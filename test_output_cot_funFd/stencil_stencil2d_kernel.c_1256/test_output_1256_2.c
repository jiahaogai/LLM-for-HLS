#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 8; j < 8192; j += 8) {
      elem = 0;
      k_col = j - 8;
      k_row = i - 8;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        int k_idx = k_row + k;
        if (k_idx < 0 || k_idx > 8183) {
          k_idx = 0;
        }
        int k_idx_1 = k_col + k_idx * 8;
        elem += orig[k_idx_1] * filter[k];
      }
      sol[j] = elem;
    }
  }
}