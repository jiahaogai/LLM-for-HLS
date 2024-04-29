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
  long j_col;
  long i_col;
<<<<<<< HEAD
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_pad;
  long end_pad;
  long start_pad;
  long pad_row;
  long pad_col;
  long pad_front;
  long pad_back;
  long flatten_size;
  long flatten_pad_size;
  long flatten_idx;
  long mult;
  long mult_pad;
=======
  long buf[25][25][25];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
<<<<<<< HEAD
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k < 40L; k++) {
=======
/* Standardize from: for(k = 0; k < 25; k++) {...} */
  for (k = 0L; k <= 24L; k++) {
    long k_col_tmp = k - 1;
    long k_col = (k_col_tmp < 0 ? 0 : k_col_tmp);
    long k_row_tmp = k + 1;
    long k_row = (k_row_tmp > 24 ? 24 : k_row_tmp);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
<<<<<<< HEAD
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j < 40L; j++) {
=======
/* Standardize from: for(j = 0; j < 25; j++) {...} */
    for (j = 0L; j <= 24L; j++) {
      long j_col_tmp = j - 1;
      long j_col = (j_col_tmp < 0 ? 0 : j_col_tmp);
      long j_row_tmp = j + 1;
      long j_row = (j_row_tmp > 24 ? 24 : j_row_tmp);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
<<<<<<< HEAD
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i < 40L; i++) {
        i_row = 40L * k + i;
        j_row = 40L * j;
        k_row = 40L * k;
        idx_row = i_row * 40L + j;
        loop_k_col:
/* Standardize from: for(k_col = k - 1; k_col <= k + 1; k_col++) {...} */
        for (k_col = ((long )0); k_col < ((long )4); k_col++) {
          true_k_col = k + k_col;
          idx_col = idx_row + 40L * k_col;
          loop_j_col:
/* Standardize from: for(j_col = j - 1; j_col <= j + 1; j_col++) {...} */
          for (j_col = ((long )0); j_col < ((long )4); j_col++) {
            true_j_col = j + j_col;
            loop_i_col:
/* Standardize from: for(i_col = i - 1; i_col <= i + 1; i_col++) {...} */
            for (i_col = ((long )0); i_col < ((long )4); i_col++) {
              true_i_col = i + i_col;
              idx = idx_col + i_col;
              if ((((true_i_col >= 0L) && (true_i_col < 40L)) && ((true_j_col >= 0L) && (true_j_col < 40L))) && ((true_k_col >= 0L) && (true_k_col < 40L))) {
                tmp = orig[idx];
              }
               else {
                tmp = 0.0;
              }
              sol[idx] = ((1.0 / 48.0) * (((4.0 * tmp) + orig[idx_col + 1L]) + orig[idx_col - 1L] + orig[idx_row + 1L] + orig[idx_row - 1L] + orig[idx_pad + 40L] + orig[idx_pad - 40L] + orig[idx_pad + 1L] + orig[idx_pad
=======
/* Standardize from: for(i = 0; i < 25; i++) {...} */
      for (i = 0L; i <= 24L; i++) {
        long i_col_tmp = i - 1;
        long i_col = (i_col_tmp < 0 ? 0 : i_col_tmp);
        long i_row_tmp = i + 1;
        long i_row = (i_row_tmp > 24 ? 24 : i_row_tmp);
        long idx = i + j * 25 + k * 25 * 25;
        long sum = 0L;
        loop_k_col:
/* Standardize from: for(k_col = (i - 1); k_col <= (i + 1); k_col++) {...} */
        for (k_col = ((i_col < 0) ? 0 : i_col); k_col <= ((i_col + 1) > 24 ? 24 : (i_col + 1)); k_col++) {
          loop_j_col:
/* Standardize from: for(j_col = (j - 1); j_col <= (j + 1); j_col++) {...} */
          for (j_col = ((j_col < 0) ? 0 : j_col); j_col <= ((j_col + 1) > 24 ? 24 : (j_col + 1)); j_col++) {
            loop_i_col:
/* Standardize from: for(i_col = (k - 1); i_col <= (k + 1); i_col++) {...} */
            for (i_col = ((k_col < 0) ? 0 : k_col); i_col <= ((k_col + 1) > 24 ? 24 : (k_col + 1)); i_col++) {
              sum += orig[i_col + j_col * 25 + k_col * 25 * 25] ;
            }
          }
        }
        buf[k][j][i] = sum;
      }
    }
    loop_k_row:
/* Standardize from: for(k_row = (k + 1
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
