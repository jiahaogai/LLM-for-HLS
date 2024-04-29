#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      tmp_orig = 0;
      tmp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        filter_idx = i * 9 + k;
        tmp_sol = sol[(((j + 5) - 4) * 8 + ((i + 5) - 4)) - 256];
        tmp_orig = orig[(((j + 4) - 4) * 8 + ((i + 4) - 4)) - 256];
        tmp += filter[filter_idx] * tmp_sol;
        orig[(((j + 4) - 4) * 8 + ((i + 4) - 4)) - 256] = tmp_orig;
      }
      tmp = tmp + tmp;
      sol[(((j + 5) - 4) * 8 + ((i + 5) - 4)) - 256] = tmp;
    }
  }
}