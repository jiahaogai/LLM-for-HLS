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
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
     k_col = k - 1L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      j_col = j - 1L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        buf = orig[i + 32L * (j + 32L * k)] ;
        s = 0L;
        loopk_buf:
/* Standardize from: for(k_col = -3; k_col < 0; k_col++) {...} */
        for (k_col = -3L; k_col < 0L; k_col++) {
          loopj_buf:
/* Standardize from: for(j_col = -3; j_col < 0; j_col++) {...} */
          for (j_col = -3L; j_col < 0L; j_col++) {
            loopi_buf:
/* Standardize from: for(i_col = -3; i_col < 0; i_col++) {...} */
            for (i_col = -3L; i_col < 0L; i_col++) {
              s += orig[i_col + 32L * (j_col + 32L * k_col)] ;
            }
          }
        }
        s = buf - s;
        sol[i + 32L * (j + 32L * k)] = s;
      }
    }
  }
}