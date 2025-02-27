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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp_orig = orig[i * 8 + j] * filter_elem;
        tmp_sol += tmp_orig;
      }
      tmp = sol[i * 8 + j];
      tmp = tmp_sol;
    }
  }
}