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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1 + 16L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = j - 1 + 16L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        i_col = i - 1 + 16L;
        sum = 0L;
        loopbuf:
        for (long _in_buf = 0; _in_buf < 8; _in_buf++) {
          buf[_in_buf] = orig[(_in_buf + i_col - 1) + ((j_col - 1) + ((k_col - 1) * 32L)) * 39304L];
          sum += buf[_in_buf];
        }
        sol[i_col + ((j_col - 1) + (k_col - 1) * 32L) * 32768L] = sum;
      }
    }
  }
}