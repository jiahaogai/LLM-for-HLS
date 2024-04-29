#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
<<<<<<< HEAD
  long tmp;
=======
  long delta;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
<<<<<<< HEAD
  for (k = 1 + 32L; k < 32L + 1L; k++) {
=======
  for (k = 1 + 32L; k < 32 + 1L; k++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
<<<<<<< HEAD
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
=======
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
<<<<<<< HEAD
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = ((orig[i + (j + (k * 32L)) * 39304] + orig[i_col + (j + (k * 32L)) * 39304] + orig[i + (j_col + (k * 32L)) * 39304] + orig[i_col + (j_col + (k * 32L)) * 39304]) - (orig[i + (j + (k_col * 32L)) * 39304] + orig[i_col + (j + (k_col * 32L)) * 39304] + orig[i + (j_col + (k_col * 32L)) * 39304] + orig[i_col + (j_col + (k_col * 32L)) * 39304])) / (C0 * (long )8);
        tmp = buf;
        sol[i + (j + (k * 32L)) * 32768] = tmp;
=======
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = orig[i + 32L * (j + 32L * k)] ;
        delta =  (buf - ((((orig[i_col + 32L * (j_col + 32L * k_col)] + orig[i_col + 32L * (j + 32L * k_col)]) + orig[i + 32L * (j_col + 32L * k_col)]) + orig[i_col + 32L * (j + 32L * k)]) / 4L)) ;
        sol[i + 32L * (j + 32L * k)] = delta;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}