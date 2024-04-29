Code: #pragma ACCEL kernel

void kernel_stencil(long C0,long C1,long orig[39304],long sol[32768])
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
  long buf;
  long tmp_col;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 1L - 3L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j <= 32L + 1L - 2L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i <= 32L + 1L - 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        idx_col = i_col + 32L * (j_col + 32L * k_col);
        idx = i + 32L * (j + 32L * k);
        t = orig[idx_col] + 2L * (orig[idx_col + 1L] + orig[idx_col + 32L] + orig[idx_col + 32L * 2L] + orig[idx_col + 32L * 3L] + orig[idx_col + 32L * 4L] + orig[idx_col + 32L * 5L] + orig[idx_col + 32L * 6L] + orig[idx_col + 32L * 7L] + orig[idx_col + 32L * 8L] + orig[idx_col + 32L * 9L] + orig[idx_col + 32L * 10L] + orig[idx_col + 32L * 11L] + orig[idx_col + 32L * 12L] + orig[idx_col + 32L * 13L] + orig[idx_col + 32L * 14L] + orig[idx_col + 32L * 15L] + orig[idx_col + 32L * 16L] + orig[idx_col + 32L * 17L] + orig[idx_col + 32L * 18L] + orig[idx_col + 32L * 19L] + orig[idx_col + 32L * 20L] + orig[idx_col + 32L * 21L] + orig[idx_col + 32L * 22L] + orig[idx_col + 32L * 23L] + orig[idx_col + 32L * 24L] + orig[idx_col + 32L * 25L] + orig[idx_col + 32L * 26L] + orig[idx_col + 32L * 27L] + orig[idx_col + 32L * 28L] + orig[idx_col + 32L * 29L] + orig[idx_col + 3