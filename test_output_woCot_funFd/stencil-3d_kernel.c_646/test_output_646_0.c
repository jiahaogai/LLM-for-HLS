#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long delta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1 + 16L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = j - 1 + 16L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        i_col = i - 1 + 16L;
        buf = orig[i + ((j + (k * 32L))) * 39304L] + ((orig[i_col + ((j + (k * 32L))) * 39304L] + orig[i_col + ((j_col) + ((k * 32L) * 32L)) * 39304L]) + orig[i + ((j_col) + ((k * 32L) * 32L)) * 39304L]);
        delta = buf - sol[i + ((j + (k * 32L))) * 32768L];
        sol[i + ((j + (k * 32L))) * 32768L] = buf;
      }
    }
  }
}