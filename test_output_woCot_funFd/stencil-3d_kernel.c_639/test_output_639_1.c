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
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j <= 32L + 32L - 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i <= 32L + 32L - 1L; i++) {
        i_row = i + 16L - 1L;
        j_row = j + 16L - 1L;
        k_row = k + 16L - 1L;
        idx_row = i_row * 32L + j_row * 3L + k_row;
        i_col = i + 1L - 1L;
        j_col = j + 1L - 1L;
        k_col = k + 1L - 1L;
        idx_col = i_col * 32L + j_col * 3L + k_col;
        t = 0L;
        loop_k_col:
/* Standardize from: for(k_col = k + 1; k_col < 32 + 1; k_col++) {...} */
        for (k_col = k + 1L; k_col <= 32L + 1L; k_col++) {
          idx = idx_col + (k_col - 1L) * 32L;
          t += orig[idx] * 2L;
        }
        loop_j_col:
/* Standardize from: for(j_col = j + 1; j_col < 32 + 1; j_col++) {...} */
        for (j_col = j + 1L; j_col <= 32L + 1L; j_col++) {
          idx = idx_col + (j_col - 1L) * 3L;
          t += orig[idx] * 4L;
        }
        idx = idx_row + (k_col - 1L) * 3L;
        sol[idx] = t;
      }
    }
  }
}