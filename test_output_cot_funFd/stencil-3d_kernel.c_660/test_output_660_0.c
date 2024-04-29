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
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 - 1 - k;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40 - 1 - j;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40 - 1 - i;
        buf = C0 * (orig[i + 40 * (j + 40 * k)]);
        buf += C1 * (orig[i_col + 40 * (j + 40 * k)] + orig[i + 40 * (j_col + 40 * k)] + orig[i_col + 40 * (j_col + 40 * k)]);
        idx = i + 40 * (j + 40 * k);
        sol[idx] = buf;
      }
    }
  }
}