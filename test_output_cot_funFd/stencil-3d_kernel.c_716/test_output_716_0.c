#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[8];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 8; k++) {...} */
  for (k = 8L; k < 32L + 1L - 8L; k++) {
     k_col = k - 4L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 8; j++) {...} */
    for (j = 8L; j < 32L + 1L - 8L; j++) {
      j_col = j - 4L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 8; i++) {...} */
      for (i = 8L; i < 32L + 1L - 8L; i++) {
        i_col = i - 4L;
        sum = 0L;
        loopbuf:
        for (long _in_buf = 0L; _in_buf < 8L; _in_buf++) {
          buf[_in_buf] = orig[(((((k_col * 32L + j_col) * 32L) + i_col) * 8L) + _in_buf) - 1L];
          sum += buf[_in_buf];
        }
        sol[(((((k * 32L + j) * 32L) + i) * 8L) + 0L) - 1L] = sum;
      }
    }
  }
}