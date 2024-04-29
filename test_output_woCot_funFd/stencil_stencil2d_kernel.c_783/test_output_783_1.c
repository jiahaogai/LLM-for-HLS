Code: 
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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=tmp_orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp = orig[i + ((k - 4) << 11)];
        tmp_orig += filter_elem * tmp;
        tmp = sol[i + ((k - 4) << 11)];
        tmp_sol += filter_elem * tmp;
      }
      tmp_sol = tmp_sol + tmp_orig;
      sol[i + (4 << 11)] = tmp_sol;
    }
  }
}