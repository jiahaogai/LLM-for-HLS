### Instructions:
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 392; k++) {...} */
  for (k = 2L; k <= 392L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 392; j++) {...} */
    for (j = 2L; j <= 392L - 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 392; i++) {...} */
      for (i = 2L; i <= 392L - 1L; i++) {
        i_row = i + 1L;
        j_row = j + 1L;
        k_row = k + 1L;
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        idx_col = i_col + 392L * (j_col + 392L * k_col);
        idx_row = i_row + 392L * (j_row + 392L * k_row);
        idx = i + 392L * (j + 392L * k);
        t = C0 * (orig[idx_col] + orig[idx_row]) - C1 * orig[idx];
        sol[idx] = t;
      }
    }
  }
}