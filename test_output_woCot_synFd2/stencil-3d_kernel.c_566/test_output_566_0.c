#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        idx_col = (((i_col - 1) * 40) + (j_col - 1)) * 40 + (k_col - 1);
        sum0 = orig[idx_col];
        mul0 = sum0 * 3;
        i = 0;
        loopk_row:
/* Standardize from: for(k_row = 0;k_row < 40;k_row++) {...} */
        for (k_row = 0; k_row < 40; k_row++) {
          j = 0;
          loopj_row:
/* Standardize from: for(j_row = 0;j_row < 40;j_row++) {...} */
          for (j_row = 0; j_row < 40; j_row++) {
            i = 0;
            loopi:
/* Standardize from: for(i = 0;i < 40;i++) {...} */
            for (i = 0; i < 40; i++) {
              idx_row = (((i - 1) * 40) + (j_row - 1)) * 40 + (k_row - 1);
              idx = (((i - 1) * 40) + (j - 1)) * 40 + (k - 1);
              sum1 = orig[idx_row] + mul0 - orig[idx];
              mul1 = sum1 * 2;
              sol[idx] = mul1;
            }
            j++;
          }
          k++;
        }
        i_col++;
      }
      j_col++;
    }
    k_col++;
  }
}