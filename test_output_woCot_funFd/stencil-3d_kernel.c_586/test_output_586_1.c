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
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long index;
  long buf;
=======
  long t;
  long x;
  long y;
  long z;
  long x1;
  long y1;
  long z1;
  long x2;
  long y2;
  long z2;
  long x3;
  long y3;
  long z3;
  long x4;
  long y4;
  long z4;
  long x5;
  long y5;
  long z5;
  long i_col;
  long j_col;
  long k_col;
  long i_row;
  long j_row;
  long k_row;
  long i_tmp;
  long j_tmp;
  long k_tmp;
  long t_col;
  long t_row;
  long t_tmp;
  long C0_idx;
  long C1_idx;
  long orig_idx;
  long sol_idx;
  C0_idx = 0;
  C1_idx = 1;
  i_col = 2;
  j_col = 2 * 390;
  k_col = 2 * 390 * 386;
  i_row = 1;
  j_row = 390;
  k_row = 390 * 386;
  t_col = 0;
  t = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L - 3L; k++) {
=======
  loop_x1:
  for (x1 = 1; x1 < 390 - 1; x1++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L - 3L; j++) {
=======
    loop_y1:
    for (y1 = 1; y1 < 390 - 1; y1++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L - 3L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        index = i_col + 32L * (j_col + 32L * k_col);
        buf = ((orig[index + 1L]) + (orig[index + 32L]) + (orig[index + 32L * 32L]) + (orig[index + 32L * 32L + 1L]) + (orig[index + 32L * 32L + 32L]) + (orig[index + 32L * 32L + 32L * 2L]) + (orig[index + 32L * 32L + 32L * 3L]) + (orig[index + 32L * 32L + 32L * 4L]) + (orig[index + 32L * 32L + 32L * 5L]) + (orig[index + 32L * 32L + 32L * 6L]) + (orig[index + 32L * 32L + 32L * 7L]) + (orig[index + 32L * 32L + 32L * 8L]) + (orig[index + 32L * 32L + 32L * 9L]) + (orig[index + 32L * 32L + 32L * 10L]) + (orig[index + 32L * 32L + 32L * 11L]) + (orig[index + 32L * 32L + 32L * 12L]) + (orig[index + 32L * 32L + 32L * 13L]) + (orig[index + 32L * 32L + 32L * 14L]) + (orig[index + 32L * 32L + 32L * 15L]) + (orig[index + 32L * 32L + 32L * 16L]) + (orig[index + 32L * 32L + 32L * 17L]) + (orig[index + 32L * 32L + 32L * 18L]) + (orig[index + 32L * 32L + 32L * 19L]) + (orig[index + 32L * 32L + 32L * 2
=======
      loop_z1:
      for (z1 = 1; z1 < 386 - 1; z1++) {
        i_tmp = x1 * i_row;
        j_tmp = y1 * j_row;
        k_tmp = z1 * k_row;
        t_tmp = x1 + y1 * 390 + z1 * 390 * 386;
        loop_t:
        for (t = 0; t < 32768; t++) {
          orig_idx = i_tmp + j_tmp + k_tmp + t_tmp;
          sol[t] = ((C0 * orig[orig_idx - 2 - k_row]) + (C1 * orig[orig_idx - 1 - k_row]) + (C0 * orig[orig_idx + 1 - k_row]) + (C1 * orig[orig_idx + 2 - k_row]) + (C0 * orig[orig_idx - 2]) + (C1 * orig[orig_idx - 1]) + (C0 * orig[orig_idx + 1]) + (C1 * orig[orig_idx + 2]) + (C0 * orig[orig_idx - 2 + k_row]) + (C1 * orig[orig_idx - 1 + k_row]) + (C0 * orig[orig_idx + 1 + k_row]) + (C1 * orig[orig_idx + 2 + k_row])) / (C1 * 8);
        }
      }
    }
  }
  z1 = 386 - 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_x2:
  for (x2 = 390; x2 < 39304; x2++) {
    
#
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
