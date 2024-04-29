#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        idx = (((32 + 1) * ((32 + 1) * k + j)) + i);
        idx_col = (((32 + 1) * ((32 + 1) * k + j)) + (i - 1));
        k_col = (((32 + 1) * (k - 1)) + j);
        i_col = (((32 + 1) * k) + (j - 1));
        C0_idx = 1 + k_col + i_col * (32 + 1);
        C1_idx = 1 + ((32 + 1) * (32 + 1)) + k_col + i_col * (32 + 1);
        tmp = ((C0 * (orig[C0_idx - 1] + orig[C0_idx + 1])) + (C1 * (orig[C1_idx - 1] + orig[C1_idx + 1]))) - orig[idx];
        sol[idx] = tmp;
      }
    }
  }
}