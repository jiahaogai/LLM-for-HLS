#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[39304],double sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
     k_col = k - 1;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      j_col = j - 1;
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        i_col = i - 1;
        tmp = ((double )0);
        loop_k_col:
/* Standardize from: for(k_col = k - 1; k_col > k - 3; k_col--) {...} */
        for (k_col = k_col - 1; k_col > k_col - 3 + 0; k_col--) {
          loop_j_col:
/* Standardize from: for(j_col = j - 1; j_col > j - 3; j_col--) {...} */
          for (j_col = j_col - 1; j_col > j_col - 3 + 0; j_col--) {
            loop_i_col:
/* Standardize from: for(i_col = i - 1; i_col > i - 3; i_col--) {...} */
            for (i_col = i_col - 1; i_col > i_col - 3 + 0; i_col--) {
              tmp += orig[i_col + 32 * (j_col + 32 * k_col)] * 4.0;
            }
          }
        }
        sol[i + 32 * (j + 32 * k)] = tmp;
      }
    }
  }
}