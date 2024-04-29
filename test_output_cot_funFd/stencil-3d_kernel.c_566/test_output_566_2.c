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
/* Standardize from: for(k_col = 1;k_col < 32 - 1;k_col++) {...} */
  for (k_col = 1; k_col <= 32 - 1; k_col++) {
     loopj_col:
/* Standardize from: for(j_col = 1;j_col < 32 - 1;j_col++) {...} */
    for (j_col = 1; j_col <= 32 - 1; j_col++) {
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 32 - 1;i_col++) {...} */
      for (i_col = 1; i_col <= 32 - 1; i_col++) {
        idx_col = (((32 * (32 - 1)) * (32 - 1)) + ((32 - 1) * 2 - 1) + (32 - 1)) - 
           (32 - 1) * (i_col + (32 - 1) * (j_col + 32 * (k_col - 1))) - 1;
        sum0 = orig[idx_col - 1] + orig[idx_col - 32] + orig[idx_col - 960] + 
          orig[idx_col + 1] + orig[idx_col + 32] + orig[idx_col + 960] - 
          4 * orig[idx_col];
        sum1 = orig[idx_col - 32 - 1] + orig[idx_col - 32 + 1] + orig[idx_col + 
          960 - 1] + orig[idx_col + 960 + 1] - 2 * orig[idx_col - 1 - 32] - 
          2 * orig[idx_col + 1 - 32] - 2 * orig[idx_col - 1 + 960] - 2 * 
          orig[idx_col + 1 + 960];
        mul0 = sum0 * 30;
        mul1 = sum1 * 30;
        sol[idx_col] = ((mul0 + mul1) > 255 ? 255 : ((mul0 + mul1) < 0 ? 
          0 : (mul0 + mul1)));
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk_row:
/* Standardize from: for(k_row = 32 - 1;k_row > 0;k_row--) {...} */
  for (k_row = 32 - 1; k_row >= 1; k_row--) {
     loopj_row:
/* Standardize from: for(j_row = 32 - 1;j_row > 0;j_row--) {...} */
    for (j_row = 32 - 1; j_row >= 1; j_row--) {
      loopi:
/* Standardize from: for(i = 0;i < 32;i++) {...} */
      for (i = 0; i < 32; i++) {
        idx_row = (32 * (32 - 1) * (32 - 1)) + ((32 - 1) * 2 * (32 - 1 - 
          k_row)) + ((32 - 1) - j_row);
        idx = idx_row + 1;
        sum0 = orig[idx] + orig[idx + 32] + orig[idx + 960] - orig[idx - 
          1] - orig[idx - 32] - orig[idx - 960];
        sum1 = orig[idx + 32 + 1] + orig[idx + 32 - 1] + orig[idx + 960 + 
          1] + orig[idx + 960 - 1] - orig[idx - 1 - 32] - orig[idx - 32 - 1] - 
          orig[idx - 1 + 960] - orig[idx - 960 - 1];
        mul0 = sum0 * 2;
        mul1 = sum1 * 2;
        sol[idx] = ((mul0 + mul1) > 255 ? 255 : ((mul0 + mul1) < 0 ? 0 : (
                  mul0 + mul1)));
      }
    }
  }
}