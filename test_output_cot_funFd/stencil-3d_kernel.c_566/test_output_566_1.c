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
  long mul0;
  long mul1;
  long sum0;
  long sum1;
  long C0P1;
  long C1P1;
  long C2P1;
  
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
      j_col = 1L + (40L * j);
      j_row = (40L * (j - 1)) + 1L;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 1L + (40L * i);
        i_row = (40L * (i - 1)) + 1L;
        mul0 = orig[i_col + j_col] * 4L;
        mul1 = orig[i_col + k_col] * 4L;
        sum0 = mul0 + mul1;
        mul0 = orig[j_col + k_col] * 4L;
        mul1 = sum0;
        sum1 = mul0 + mul1;
        orig[i_row + j_row] = sum1;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk_1:
/* Standardize from: for(k = 1; k < 40 - 1; k++) {...} */
  for (k = 1 + 1; k < 40 + 1 - 1; k++) {
     C0P1 = C0 + 1L;
     k_col = 40L * k;
     k_row = (40L * (k - 1)) + 1L;
     loopj_1:
/* Standardize from: for(j = 1; j < 40 - 1; j++) {...} */
    for (j = 1 + 1; j < 40 + 1 - 1; j++) {
      C1P1 = C1 + 1L;
      j_col = 1L + (40L * j);
      j_row = (40L * (j - 1)) + 1L;
      loopi_1:
/* Standardize from: for(i = 1; i < 40 - 1; i++) {...} */
      for (i = 1 + 1; i < 40 + 1 - 1; i++) {
        C2P1 = C2 + 1L;
        i_col = 1L + (40L * i);
        i_row = (40L * (i - 1)) + 1L;
        idx = i_row + j_row;
        idx_col = i_col + j_col;
        idx_row = i_row + k_row;
        mul0 = orig[idx_col] * 2L;
        mul1 = orig[idx_row] * 2L;
        sum0 = mul0 + mul1;
        mul0 = sum0 + orig[idx];
        mul1 = mul0 + orig[idx_row + C0P1];
        sum1 = mul0 + mul1;
        sol[idx] = sum1;
      }
    }
  }
}