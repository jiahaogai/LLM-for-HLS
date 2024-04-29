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
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32 - 1;j-- > 0 + 1;) {
    long j_col_tmp = j * 32;
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1;k-- > 0 + 1;) {
      long k_col_tmp = k * 32;
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32 - 1;i-- > 0 + 1;) {
        long i_col_tmp = i * 32;
        buf = orig[i_col_tmp + k_col_tmp + j_col_tmp];
        sol[i_col_tmp + k_col_tmp + j_col_tmp] = C0 * buf + C1 * (sol[i_col_tmp + k_col_tmp + j_col_tmp - 1] + sol[i_col_tmp + k_col_tmp + j_col_tmp + 1] + sol[i_col_tmp + k_col_tmp - 1 + j_col_tmp] + sol[i_col_tmp + k_col_tmp + 1 + j_col_tmp] + sol[i_col_tmp - 1 + k_col_tmp + j_col_tmp] + sol[i_col_tmp + 1 + k_col_tmp + j_col_tmp]);
      }
    }
  }
}