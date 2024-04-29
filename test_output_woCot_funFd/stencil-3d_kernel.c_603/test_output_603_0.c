#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
<<<<<<< HEAD
  long t1;
  long t2;
  long t3;
=======
  long t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
<<<<<<< HEAD
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
=======
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1 - 3; k++) {
      k_col = 32 * k;
=======
    loopk_col:
    for (k_col = 1 + 32 - 1; k_col < 32 + 1; k_col++) {
      i_col = 1 + 32 - 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 3; i++) {
        i_col = 32 * i;
        idx = i_col + k_col;
        idx_col = k_col + i_col;
        t1 = orig[idx_col - 1] + orig[idx_col + 1];
        t2 = orig[idx_col] + orig[idx_col + 32];
        t3 = orig[idx_col - 32] + orig[idx_col];
        sol[idx] = C0 * (t1 + t2) + C1 * (t3 + orig[idx]);
=======
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      while (i_col <= 32 + 1 - 3) {
        idx_col = (k_col - 1) * (32 + 1) * (32 + 1) + (i_col - 1) * (32 + 1) + j - 1;
        t = orig[idx_col] + 32L * 32L * C0 * (orig[idx_col + 32L] + orig[idx_col + 32L * (32L + 1)]);
        idx = (k - 1) * (32 + 1) * (32 + 1) + (i - 1) * (32 + 1) + j;
        sol[idx] = t;
        i_col++;
        idx_col++;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}