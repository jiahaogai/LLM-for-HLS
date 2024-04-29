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
  long s;
=======
  long idx;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
<<<<<<< HEAD
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
=======
  for (k = 1 + 32L; k > 32L; k--) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
<<<<<<< HEAD
    for (j = 1 + 2; j-- > 32 + 1L; ) {
=======
    for (j = 1 + 32L; j > 32L; j--) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
<<<<<<< HEAD
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        s = C0 * (orig[i + 32L * (j + 32L * k)]);
        buf = C1 * (orig[i_col + 32L * (j + 32L * k)] + orig[i + 32L * (j_col + 32L * k)] + orig[i + 32L * (j + 32L * k_col)]);
        s =  buf - s;
        sol[i + 32L * (j + 32L * k)] = s;
=======
      for (i = 1 + 32L; i > 1L; i--) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        j_col = (32L + 1L) * j;
        i_col = i;
        buf = orig[k_col + j_col + i_col] + C0 * (orig[k_col + j_col + i_col - 1L] + orig[k_col + j_col + i_col + 1L] + orig[k_col + j_col - 1L + i_col] + orig[k_col + j_col + 1L + i_col] + orig[k_col - 1L + j_col + i_col] + orig[k_col + 1L + j_col + i_col] + orig[k_col - 1L + j_col - 1L + i_col] + orig[k_col + 1L + j_col - 1L + i_col] + orig[k_col - 1L + j_col + 1L + i_col] + orig[k_col + 1L + j_col + 1L + i_col]);
        idx = k_col + j_col + i_col;
        sol[idx] = buf;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk2:
/* Standardize from: for(k = 32 + 1 - 3; k < 32 + 1; k++) {...} */
  for (k = 32L + 1L; k < 32L + 1L + 3L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj2:
/* Standardize from: for(j = 32 + 1 - 2; j < 32 + 1; j++) {...} */
    for (j = 32L + 1L; j < 32L + 1L + 2L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi2:
/* Standardize from: for(i = 32 + 1 - 1; i < 32 + 1; i++) {...} */
      for (i = 32L + 1L; i < 32L + 1L + 1L; i++) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        j_col = (32L + 1L) * j;
        i_col = i;
        buf = orig[k_col + j_col + i_col] + C1 * (orig[k_col + j_col + i_col - 1L] + orig[k_col + j_col + i_col + 1L] + orig[k_col + j_col - 1L + i_col] + orig[k_col + j_col + 1L + i_col] + orig[k_col - 1L + j_col + i_col] + orig[k_col + 1L + j_col + i_col] + orig[k_col - 1L + j_col - 1L + i_col] + orig[k_col + 1L + j_col - 1L + i_col] + orig[k_col - 1L + j_col + 1L + i_col] + orig[k_col + 1L + j_col + 1L + i_col]);
        idx = k_col + j_col + i_col;
        sol[idx] = buf;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}