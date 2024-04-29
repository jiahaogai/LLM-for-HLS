#pragma ACCEL kernel

<<<<<<< HEAD
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
=======
void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
<<<<<<< HEAD
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long sum0;
  long sum1;
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        i_row = i + 31L;
        j_row = j + 31L;
        k_row = k + 31L;
        sum0 = ((orig[i_row * 32L + j_row * 32L + k_row] + orig[i_row * 32L + j_row * 32L + k_col] + orig[i_row * 32L + j_col * 32L + k_row]) + (orig[i_row * 32L + j_col * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_row] + orig[i_col * 32L + j_row * 32L + k_col])) + (orig[i_col * 32L + j_col * 32L + k_row] + orig[i_col * 32L + j_col * 32L + k_col]);
        sum1 = ((orig[i_row * 32L + j_row * 32L + k_col] + orig[i_row * 32L + j_row * 32L + k_row] + orig[i_row * 32L + j_col * 32L + k_row]) + (orig[i_row * 32L + j_col * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_col] + orig[i_col * 32L + j_row * 32L + k_row])) + (orig[i_col * 32L + j_col * 32L + k_row] + orig[i_col * 32L + j_col * 32L + k_col]);
        mul0 = sum0 * 32L;
        mul1 = sum1 * 32L;
        sol[i * 32L + j * 32L + k] = ((mul0 + mul1) + 160L) >> 8;
      }
    }
  }
}
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
