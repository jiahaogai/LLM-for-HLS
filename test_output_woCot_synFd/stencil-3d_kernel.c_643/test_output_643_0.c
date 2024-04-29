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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0; k++) {
     k_col = 40 - k;
     delta = 1 - k_col;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0; j++) {
      j_col = 40 - j;
      delta += 1 - j_col;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0; i++) {
        i_col = 40 - i;
        delta += 1 - i_col;
        buf = orig[i + 1 + (j + 1) * 40 + (k + 1) * 40 * 40] + orig[i + 1 + (j + 0) * 40 + (k + 0) * 40 * 40] + orig[i + 1 + (j + 0) * 40 + (k + 1) * 40 * 40] + orig[i + 0 + (j + 1) * 40 + (k + 1) * 40 * 40] + orig[i + 0 + (j + 0) * 40 + (k + 0) * 40 * 40] + orig[i + 0 + (j + 0) * 40 + (k + 1) * 40 * 40] + orig[i + 0 + (j + 1) * 40 + (k + 0) * 40 * 40];
        sol[i + (j + (k * 40)) * 40] = ((buf + delta) / 8);
      }
    }
  }
}