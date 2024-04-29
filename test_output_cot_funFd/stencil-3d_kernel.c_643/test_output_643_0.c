#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0; k++) {
     k_col = 40 - k;
     bound = ((k + 1) * 40) * 39;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0; j++) {
      j_col = 40 - j;
      i_col = k_col * 39 + j_col;
      t = orig[i_col] + ((j_col * 40) * 2 + k_col) * 2;
      loop_i:
/* Standardize from: for(i = 1; i < 39; i++) {...} */
      for (i = 1 + 0; i <= 39 + 0; i++) {
        i_col = i + (j * 39) + (k * 39 * 40);
        t += orig[i_col] + ((j_col * 40) * 2 + k_col) * 2;
      }
      sol[i_col] = t;
    }
  }
}