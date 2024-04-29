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
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_row = i + 1L - 1L;
        j_row = j + 1L - 1L;
        k_row = k + 1L - 1L;
        idx_row = i_row * (32L + 1L) * (32L + 1L) + j_row * (32L + 1L) + k_row;
        sum = 0L;
        loopk_col:
        for (k_col = k - 1L; k_col <= k + 1L; k_col++) {
          loopj_col:
          for (j_col = j - 1L; j_col <= j + 1L; j_col++) {
            loopi_col:
            for (i_col = i - 1L; i_col <= i + 1L; i_col++) {
              idx_col = i_col * (32L + 1L) * (32L + 1L) + j_col * (32L + 1L) + k_col;
              sum += orig[idx_col] * 4L;
            }
          }
        }
        sol[idx_row] = sum;
      }
    }
  }
}