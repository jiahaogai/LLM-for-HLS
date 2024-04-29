<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
<<<<<<< HEAD
  for (i = 0; i < 40; i++) {
=======
  for (i = 1; i < 32 + 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
<<<<<<< HEAD
    for (j = 0; j < 40; j++) {
      loop_k_col:
      for (k_col = 0; k_col < 40; k_col++) {
        i_col = i - 1 + (-1 + 0);
        if (i_col < 0) {
          i_col += 40;
        }
         else {
          if (i_col > 39) {
            i_col -= 40;
          }
        }
        j_col = j - 1 + (-1 + 0);
        if (j_col < 0) {
          j_col += 40;
        }
         else {
          if (j_col > 39) {
            j_col -= 40;
          }
        }
        k_row = k - 1 + (-1 + 0);
        if (k_row < 0) {
          k_row += 40;
        }
         else {
          if (k_row > 39) {
            k_row -= 40;
          }
        }
        i_row = i - 1 + (-1 + 1);
        if (i_row < 0) {
          i_row += 40;
        }
         else {
          if (i_row > 39) {
            i_row -= 40;
          }
        }
        j_row = j - 1 + (-1 + 1);
        if (j_row < 0) {
          j_row += 40;
        }
         else {
          if (j_row > 39) {
            j_row -= 40;
          }
        }
        idx_col = i_col * 40 + j_col;
        idx_row = i_row * 40 + j_row;
        idx = idx_col * 4 + idx_row;
        t = C0 * (orig[idx_col * 40 + idx_row] - 2 * orig[idx] + orig[idx_row * 40 + idx_col]);
        t += C1 * (orig[idx] - orig[idx_col * 40 + idx_row]);
        sol[idx] = t;
      }
      loop_k_row:
      for (k_row = 0; k_row < 40; k_row++) {
        i_row = i - 1 + (-1 + 1);
        if (i_row < 0) {
          i_row += 40;
        }
         else {
          if (i_row > 39) {
            i_row -= 40;
          }
        }
        j_row = j - 1 + (-1 + 1);
        if (j_row < 0) {
          j_row += 40;
        }
         else {
          if (j_row > 39) {
            j_row -= 40;
          }
        }
        idx_row = i_row * 40 + j_row;
        t = C0 * (orig[idx_row] - 2 * orig[idx] + orig[idx_col * 40 + idx_row]) + C
=======
    for (j = 1; j < 32 + 1; j++) {
      loop_k_col:
      for (k_col = 0; k_col < 32 + 1; k_col++) {
        i_col = i - 1 + k_col;
        if (((i_col >= 0) && (i_col < 32 + 1))) {
          idx_col = i_col * (32 + 1) * (32 + 1);
          loop_k_row:
          for (k_row = 0; k_row < 32 + 1; k_row++) {
            j_row = j - 1 + k_row;
            if (((j_row >= 0) && (j_row < 32 + 1))) {
              idx_row = idx_col + j_row * (32 + 1);
              t = (((C0 * (long )orig[idx_row + k_col]) + (C1 * (long )orig[idx_row - (32 + 1)])) + (C0 * (long )orig[idx_row + (32 + 1)]) + (C1 * (long )orig[idx_row - 1])) + (C1 * (long )orig[idx_row + 1]);
              sol[idx_row + k_row] = t;
            }
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
    for (k = 1; k < 32 + 1; k++) {
      i_row = i - 1 + k;
      if (((i_row >= 0) && (i_row < 32 + 1))) {
        idx_row = i_row * (32 + 1) * (32 + 1);
        loop_j_row:
        for (j_row = 0; j_row < 32 + 1; j_row++) {
          idx = idx_row + j_row;
          sol[idx] = ((2 * (long )sol[idx]) - sol[idx - (32 + 1)] - sol[idx + (32 + 1)] - sol[idx - 1] - sol[idx + 1]) / (long )C0;
        }
      }
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
