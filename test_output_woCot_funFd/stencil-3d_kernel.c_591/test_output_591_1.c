<<<<<<< HEAD
#pragma ACCEL kernel
=======
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        i_col = i - 1 + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        j_col = j - 1 + ((k - 1) * 32);
        k_col = k - 1;
        t1 = orig[i_col - 1] + orig[i_col + 1];
        t2 = orig[j_col - 1 + 32 * 32] + orig[j_col + 1 + 32 * 32];
        t3 = orig[k_col - 1 + 32 * 32 * 32] + orig[k_col + 1 + 32 * 32 * 32];
        bound = ((((i - 1) * (32 - 1)) + (j - 1)) * (32 - 1)) + (k - 1);
        sol[bound] = ((C0 * orig[bound]) + (C1 * (t1 + t2 + t3))) / 32;
      }
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
