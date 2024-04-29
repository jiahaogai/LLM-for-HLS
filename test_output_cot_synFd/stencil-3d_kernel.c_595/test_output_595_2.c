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
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 4; k++) {...} */
  for (k = 1 + 0; k < 4 + 0; k++) {
     k_col = 4 * k;
     loopj:
/* Standardize from: for(j = 1; j < 4; j++) {...} */
    for (j = 1 + 0; j < 4 + 0; j++) {
      j_col = 4 * j;
      loopi:
/* Standardize from: for(i = 1; i < 4; i++) {...} */
      for (i = 1 + 0; i < 4 + 0; i++) {
        i_col = 4 * i;
        bound = (C0 - 4) * (C1 - 4) * (C1 - 4);
        t1 = orig[i_col + j_col + k_col] >> 1;
        t2 = orig[i_col + j_col + 1 + k_col] >> 1;
        t3 = orig[i_col + 1 + j_col + k_col] >> 1;
        sol[i_col + j_col + k_col] = ((t1 + t2 + t3) / (bound)) + 16;
      }
    }
  }
}