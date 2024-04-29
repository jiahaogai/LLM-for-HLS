#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
  for (j_col = 1; j_col < 40; j_col++) {
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
    for (k_col = 1; k_col < 40; k_col++) {
      idx_col = (((40 * 40) * 40) * j_col) + (((40 * 40)) * k_col) + 40 * 1;
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      for (i_col = 1; i_col < 40 + 1; i_col++) {
        t = orig[idx_col - 1] + orig[idx_col + 1] + orig[idx_col + 40] + orig[idx_col - 40] + orig[idx_col + 40 * 40] + orig[idx_col - 40 * 40];
        sol[idx_col] = ((t + C0) / C1);
        idx_col++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj_row:
/* Standardize from: for(j_row = 1;j_row < 40 - 2;j_row++) {...} */
  for (j_row = 1; j_row < 40 - 2; j_row++) {
    loopk_row:
/* Standardize from: for(k_row = 1;k_row < 40 - 2;k_row++) {...} */
    for (k_row = 1; k_row < 40 - 2; k_row++) {
      idx_row = (40 * (40 - 2)) * j_row + (40 - 2) * 1 + 1 + k_row;
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_row:
      for (i_row = 1; i_row < 40 - 2; i_row++) {
        idx = idx_row - 40 * 2;
        t = orig[idx + 1] + orig[idx + 40] + orig[idx + 40 * 2] + orig[idx + 40 * 3] + orig[idx] + orig[idx + 40 * 4];
        sol[idx_row] = ((t + C0) / C1);
        idx_row++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 40 - 1;j++) {...} */
  for (j = 1; j < 40 - 1; j++) {
    loopk:
/* Standardize from: for(k = 1;k < 40 - 1;k++) {...} */
    for (k = 1; k < 40 - 1; k++) {
      idx_in = (((40 * 40) * 40) / 2) + ((40 * 40) * j) + (40 * k) + 1;
      idx = ((40 * 40) * 40) / 2 + ((40 * (j - 1)) + (k - 1)) + 1;
      t = sol[idx_in] + orig[idx_in] + sol[idx_in + 1] + sol[idx_in + 40] + sol[idx_in + 40 * 40] + sol[idx_in + 40 * 40 * 2];
      sol[idx] = ((t + C0) / C1);
    }
  }
}