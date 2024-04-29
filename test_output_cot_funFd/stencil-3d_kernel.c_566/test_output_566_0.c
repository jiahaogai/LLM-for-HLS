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
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40L * k;
     k_row = (40L * (k - 1)) + 1L;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = k_col + j;
      j_row = k_row + j;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = j_col + i;
        i_row = j_row + i;
        sum0 = orig[i_col - 1] + orig[i_col + 1] + orig[i_row - 1] + orig[i_row + 1] + orig[i_row - 40] + orig[i_row + 40];
        sum1 = orig[i_col - 40] + orig[i_col + 40] + sum0;
        mul0 = sum0 * (-2L);
        mul1 = sum1 * 2L;
        sol[i_row - 1] = mul0 + orig[i_row - 1];
        sol[i_row] = mul0 + mul1;
        sol[i_row + 1] = mul0 + orig[i_row + 1];
      }
    }
  }
}