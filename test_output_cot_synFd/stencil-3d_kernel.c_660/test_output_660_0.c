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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 * 1 * 1 + 1 * 1 + k;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40 * 1 + 1 * 1 + j;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40 * 1 + 1 + i;
        buf = C0 * (orig[i_col - 1] + orig[i_col + 1] + orig[i_col - 40] + orig[i_col + 40] + orig[i_col - 40 * 40] + orig[i_col + 40 * 40]) + C1 * orig[i_col];
        sol[i_col] = buf;
      }
    }
  }
}