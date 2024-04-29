#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 - k;
     idx_col = 0;
     loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      i_col = 40 - j;
      idx = ((k * 40) + j) * 40 + 1;
      loopi:
/* Standardize from: for(i = 1;i < 40;i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        t = orig[idx_col + i_col] + ((+1 * (orig[idx_col + i] + orig[idx_col + i + 1]))) + ((+1 * (orig[idx + i_col] + orig[idx + i_col + 1]))) + ((+1 * (orig[idx + i] + orig[idx + i + 1])));
        sol[idx++] = t;
      }
      idx_col += 40;
    }
  }
}