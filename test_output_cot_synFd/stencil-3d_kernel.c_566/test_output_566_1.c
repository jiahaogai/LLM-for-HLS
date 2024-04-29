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
     k_row = (40L * (k - 1)) + 1;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 1L + (40L * j);
      j_row = (40L * (j - 1)) + 1;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 1L + ((40L * i) + j_col);
        i_row = ((40L * (i - 1)) + 1) + j_row;
        sum0 = orig[i_row - 1] + orig[i_row + 1] + orig[i_row - 40] + orig[i_row + 40] + orig[i_row - 40 * 40] + orig[i_row + 40 * 40];
        sum1 = orig[i_col - 1] + orig[i_col + 1] + orig[i_col - 40] + orig[i_col + 40] + orig[i_col - 40 * 40] + orig[i_col + 40 * 40];
        mul0 = sum0 * 3;
        mul1 = sum1 * 3;
        sol[i_row - 1] = mul0 + orig[i_row - 1] - sum1;
        sol[i_row + 1] = mul0 + orig[i_row + 1] - sum1;
        sol[i_row - 40] = mul0 + orig[i_row - 40] - sum1;
        sol[i_row + 40] = mul0 + orig[i_row + 40] - sum1;
        sol[i_row - 40 * 40] = mul0 + orig[i_row - 40 * 40] - sum1;
        sol[i_row + 40 * 40] = mul0 + orig[i_row + 40 * 40] - sum1;
        mul0 = sum0 * 4;
        mul1 = sum1 * 4;
        idx_col = i_col + 40;
        idx_row = i_row + 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul0 + orig[idx] - sum1;
        idx_col = i_col - 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul0 + orig[idx] - sum1;
        idx_row = i_row - 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul0 + orig[idx] - sum1;
        idx_row = i_row + 40;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul0 + orig[idx] - sum1;
        idx_row = i_row - 40;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul0 + orig[idx] - sum1;
        idx_row = i_row;
        idx_col = i_col + 40;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
        idx_col = i_col - 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
        idx_row = i_row - 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
        idx_row = i_row + 1;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
        idx_row = i_row + 40;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
        idx_row = i_row - 40;
        idx = idx_row * 40L + idx_col;
        sol[idx] = mul1 + orig[idx] - sum0;
      }
    }
  }
}