#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long down;
  long up;
  long left;
  long right;
  long up_col;
  long down_col;
  long left_col;
  long right_col;
  long idx;
  long idx_col;
  long t;
  long mul;
  long sum;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        i = 40L * (40L * k_col + j_col) + i_col;
        idx_col = 40L * (40L * (k_col - 1) + j_col) + i_col;
        down_col = idx_col - 40L;
        up_col = idx_col + 40L;
        left_col = idx_col - 1;
        right_col = idx_col + 1;
        mul = 1;
        sum = 0;
/* Standardize from: for(k = 0;k < 40;k ++) {...} */
        loopk:
        for (k = 0; k < 40; k++) {
          down = down_col + k;
          up = up_col + k;
          left = left_col + k;
          right = right_col + k;
          mul0 = mul;
          if (mul0 == 0) {
            mul0 = 1;
          }
          mul1 = mul0;
          if (up >= 39304) {
            up = 39303;
          }
          if (down < 0) {
            down = 0;
          }
          if (left >= 39304) {
            left = 39303;
          }
          if (right < 0) {
            right = 0;
          }
          t = orig[up] + orig[down] + orig[left] + orig[right] - 4 * orig[idx];
          sum += mul0 * t;
          mul = mul1;
        }
        sol[idx_col] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 1;k < 40;k ++) {...} */
  for (k = 1; k < 40; k++) {
    loopj:
/* Standardize from: for(j = 1;j < 40;j ++) {...} */
    for (j = 1; j < 40; j++) {
      loopi:
/* Standardize from: for(i = 1;i < 40;i ++) {...} */
      for (i = 1; i < 40; i++) {
        idx = 40L * (40L * k + j) + i;
        orig[idx] = sol[