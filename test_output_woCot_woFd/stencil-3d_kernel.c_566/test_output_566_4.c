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
        idx_col = ((((i_col - 1) * 40) + (j_col - 1)) * 40) + (k_col - 1);
        sum0 = orig[idx_col];
        mul0 = i_col * j_col * k_col;
        sum1 = 0;
        loopk_row:
/* Standardize from: for(k_row = 1;k_row < 40;k_row++) {...} */
        for (k_row = 1; k_row < 40; k_row++) {
          loopj_row:
/* Standardize from: for(j_row = 1;j_row < 40;j_row++) {...} */
          for (j_row = 1; j_row < 40; j_row++) {
            loopi_row:
/* Standardize from: for(i_row = 1;i_row < 40;i_row++) {...} */
            for (i_row = 1; i_row < 40; i_row++) {
              idx_row = ((((i_row - 1) * 40) + (j_row - 1)) * 40) + (k_row - 1);
              sum1 += orig[idx_row] * mul0;
            }
          }
        }
        sol[idx_col] = sum1 - sum0;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 40;k < 80;k++) {...} */
  for (k = 40; k < 80; k++) {
    loopj:
/* Standardize from: for(j = 0;j < 40;j++) {...} */
    for (j = 0; j < 40; j++) {
      loopi:
/* Standardize from: for(i = 0;i < 40;i++) {...} */
      for (i = 0; i < 40; i++) {
        idx = ((((i - 1) * 40) + (j - 1)) * 40) + (k - 40);
        sum0 = 0;
        mul1 = i * j * k;
        loopk_up:
/* Standardize from: for(k_up = 1;k_up < 80 - k;k_up++) {...} */
        for (k_up = 1; k_up < 80 - k; k_up++) {
          idx_up = ((((i - 1) * 40) + (j - 1)) * 40) + (k_up + k - 1);
          sum0 += orig[idx_up] * mul1;
        }
        loopj_up:
/* Standardize from: for(j_up = 1;j_up < 80 - j;j_up++) {...} */
        for (j_up = 1; j_up < 80 - j; j_up++) {
          idx_up = ((((i - 1) * 40) + (j_up + j - 1)) * 40) + (k - 1);
          sum0 += orig[idx_up] * mul1;
        }
        loopi_up:
/* Standardize from: for(i_up = 1;i_up < 80 - i;i_up++) {...} */
        for (i_up = 1; i_up < 80 - i; i_up++) {
          idx_up = ((((i_up + i - 1) * 40) + (j - 1)) * 40) + (k - 1);
          sum0 += orig[idx_up] * mul1;
        }
        sol[idx] = sum0;
      }
    }
  }
}