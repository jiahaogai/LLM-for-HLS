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
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 - k;
     idx_col = k_col * 1 * 80;
     loop_j:
/* Standardize from: for(j = 1; j < 80; j++) {...} */
    for (j = 1 + 0; j < 80 + 0; j++) {
      i_col = 80 - j;
      idx = idx_col + i_col;
      t = orig[idx] + ((+1 * (orig[idx + 1] + orig[idx_col + i_col + 1]))) + ((+1 * (orig[idx_col + i_col]))) + ((+1 * (orig[idx_col + i_col - 1] + orig[idx - 1]))) + ((+1 * (orig[idx - 1 - 1] + orig[idx_col + i_col - 1] + orig[idx_col + i_col + 1] + orig[idx + 1 - 1] + orig[idx + 1 + 1])));
      sol[idx] = t;
    }
    idx_col = 0;
  }
}