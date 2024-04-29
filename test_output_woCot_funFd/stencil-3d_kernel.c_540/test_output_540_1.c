#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long upper_neighbor;
  long lower_neighbor;
  long left_neighbor;
  long right_neighbor;
  long front_neighbor;
  long back_neighbor;
  long tmp;
=======
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
<<<<<<< HEAD
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = 32L * k;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = 32L * j;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        i_col = 32L * i;
        upper_neighbor = orig[i_col + j_col + k_col - 1] << 1;
        lower_neighbor = orig[i_col + j_col + k_col + 1] << 1;
        left_neighbor = orig[i_col + j_col + k_col - 32] << 1;
        right_neighbor = orig[i_col + j_col + k_col + 32] << 1;
        front_neighbor = orig[i_col + j_col + k_col - 30] << 1;
        back_neighbor = orig[i_col + j_col + k_col + 30] << 1;
        tmp = ((((upper_neighbor + lower_neighbor) + (left_neighbor + right_neighbor)) + (front_neighbor + back_neighbor)) + (orig[i_col + j_col + k_col] << 2));
        sol[i_col + j_col + k_col] = tmp;
=======
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        sum = ((orig[i_col + ((j_col + (k_col * 32L))) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 2L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 3L) * 39304];
        sum += orig[i_col + 32L + ((j_col + (k_col * 32L)) * 39304)] + orig[i_col + 32L + ((j_col + (k_col * 32L)) + 32L) * 39304] + orig[i_col + 32L + ((j_col + (k_col * 32L)) + 32L * 2L) * 39304] + orig[i_col + 32L + ((j_col + (k_col * 32L)) + 32L * 3L) * 39304];
        sum += orig[i_col + 32L * 2L + ((j_col + (k_col * 32L)) * 39304)] + orig[i_col + 32L * 2L + ((j_col + (k_col * 32L)) + 32L) * 39304] + orig[i_col + 32L * 2L + ((j_col + (k_col * 32L)) + 32L * 2L) * 39304] + orig[i_col + 32L * 2L + ((j_col + (k_col * 32L)) + 32L * 3L) * 39304];
        sum += orig[i_col + 32L * 3L + ((j_col + (k_col * 32L)) * 39304)] + orig[i_col + 32L * 3L + ((j_col + (k_col * 32L)) + 32L) * 39304] + orig[i_col + 32L * 3L + ((j_col + (k_col * 32L)) + 32L * 2L) * 39304] + orig[i_col + 32L * 3L + ((j_col + (k_col * 32L)) + 32L * 3L) * 39304];
        sum += ((C1 * (orig[i_col + ((j_col + (k_col * 32L))) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L) * 39304])) + (C0 * sum));
        sol[i_col + ((j_col + (k_col * 32L)) * 32768)] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}