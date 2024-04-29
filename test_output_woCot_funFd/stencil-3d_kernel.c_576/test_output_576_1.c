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
  long buf[27];
  long sum;
=======
  long buf;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopk:
  for (k = 1; k < 32 + 1; k++) {
=======
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
<<<<<<< HEAD
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf[0] = orig[i_col + (j_col + (k_col + 0 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[1] = orig[i_col + (j_col + (k_col + 1 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[2] = orig[i_col + (j_col + (k_col + 2 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[3] = orig[i_col + (j_col + (k_col + 3 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[4] = orig[i_col + (j_col + (k_col + 4 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[5] = orig[i_col + (j_col + (k_col + 5 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[6] = orig[i_col + (j_col + (k_col + 6 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[7] = orig[i_col + (j_col + (k_col + 7 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[8] = orig[i_col + (j_col + (k_col + 8 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[9] = orig[i_col + (j_col + (k_col + 9 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[10] = orig[i_col + (j_col + (k_col + 10 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[11] = orig[i_col + (j_col + (k_col + 11 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[12] = orig[i_col + (j_col + (k_col + 12
=======
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        k_col = ((32L + 1L) * (32L + 1L) * k) - 1L;
        j_col = (32L + 1L) * j - 1L;
        i_col = 32L + 1L - 1L;
        buf = orig[k_col - 1L] + orig[k_col + 1L] + orig[j_col - 1L] + orig[j_col + 1L] + orig[i_col - 1L] + orig[i_col + 1L] - 6L * orig[k_col + j_col + i_col];
        sol[k_col + j_col + i_col] = buf;
      }
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
