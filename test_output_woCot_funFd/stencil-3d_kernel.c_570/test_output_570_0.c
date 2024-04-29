#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
<<<<<<< HEAD
  long idx_col;
  long t;
=======
  long tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
<<<<<<< HEAD
  for (k = 1 + 32L; k <= 32L + 32L; k++) {
=======
  for (k = 1 + 32L; k > 32L; k--) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
<<<<<<< HEAD
    for (j = 1 + 2L; j <= 32L + 2L; j++) {
=======
    for (j = 1 + 32L; j > 32L; j--) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
<<<<<<< HEAD
      for (i = 1 + 1L; i <= 32L + 1L; i++) {
        k_col = -(32L << 1) + k;
        i_col = -(32L << 1) + i;
        idx_col = i_col * 32L + k_col;
        t = orig[idx_col];
        idx = i * 32L * 32L + j * 32L + k;
        sol[idx] = t + ((+1L) * (orig[idx_col + 32L] + orig[idx_col + 1L])) + ((+2L) * (orig[idx_col + 33L] + orig[idx_col + 2L])) + ((+1L) * (orig[idx_col - 32L] + orig[idx_col - 1L])) + ((+2L) * (orig[idx_col - 31L] + orig[idx_col - 2L]));
=======
      for (i = 1 + 32L; i > 16L; i--) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        i_col = ((32L + 1L) * (32L + 1L)) * i;
        idx = k_col + i_col;
        tmp = 0.125L * (orig[idx - 1 - 32L - 1L] + orig[idx - 32L - 1L] + orig[idx + 1L - 32L - 1L] + orig[idx + 32L - 1L] + orig[idx - 1L] + orig[idx + 1L] + orig[idx - 32L] + orig[idx + 32L] + orig[idx - 1L + 32L] + orig[idx - 32L + 32L] + orig[idx + 1L + 32L] + orig[idx + 32L + 32L]);
        sol[idx] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}