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
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
     k_col = 32L * k;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      j_col = 32L * j;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = 32L * i;
        t1 = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[i_col + j_col + k_col];
        t2 = orig[i_col] + t1;
        t3 = C0 * (t2 - orig[i_col + 32L * 32L * 8L]);
        sol[i_col + j_col + k_col] = t3;
      }
    }
  }
}