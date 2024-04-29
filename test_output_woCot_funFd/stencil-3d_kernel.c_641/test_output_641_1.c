Code: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
  for (k = 1 + 31; k-- > 0 + 1; ) {
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 31; j-- > 0 + 1; ) {
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 31; i-- > 0 + 1; ) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx_col = i_col + 32 * (j_col + 32 * k_col);
        t = C0 * orig[idx_col] + C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + 32] + orig[idx_col - 32] + orig[idx_col + 32 * 32] + orig[idx_col - 32 * 32] + orig[idx_col + 32 * 32 * 2] + orig[idx_col - 32 * 32 * 2]);
        idx = i + 32 * (j + 32 * k);
        sol[idx] = t;
      }
    }
  }
}