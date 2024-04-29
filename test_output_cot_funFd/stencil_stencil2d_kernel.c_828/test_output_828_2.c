#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 64; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=tmp_orig FACTOR=auto{1}
      inner_orig:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp = orig[i * 64 + j + col_offsets[k]];
        tmp_orig += filter_elem * tmp;
      }
      
#pragma ACCEL PARALLEL reduction=tmp_sol FACTOR=auto{62}
      inner_sol:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp = sol[i * 64 + j + col_offsets[k]];
        tmp_sol += filter_elem * tmp;
      }
      tmp_sol = tmp_orig + tmp_sol;
      sol[i * 64 + j] = tmp_sol;
    }
  }
}