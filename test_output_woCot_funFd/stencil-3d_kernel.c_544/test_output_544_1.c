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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
<<<<<<< HEAD
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
=======
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j < 392 + 0; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = orig[i_col + 32L * (j_col + 32L * k_col)] + 
          C0 * (orig[i_col + 1L + 32L * (j_col + 32L * k_col)] + orig[i_col - 1L + 32L * (j_col + 32L * k_col)] + 
          orig[i_col + 32L * (j_col + 1L + 32L * k_col)] + orig[i_col + 32L * (j_col - 1L + 32L * k_col)] + 
          orig[i_col + 32L * (j_col + 32L * (k_col + 1L))] + orig[i_col + 32L * (j_col + 32L * (k_col - 1L))])
          + C1 * (orig[i_col + 2L + 32L * (j_col + 32L * k_col)] + orig[i_col + 2L - 1L + 32L * (j_col + 32L * k_col)] + 
          orig[i_col + 1L + 32L * (j_col + 2L + 32L * k_col)] + orig[i_col + 1L - 1L + 32L * (j_col + 2L + 32L * k_col)] + 
          orig[i_col - 1L + 32L * (j_col + 2L + 32L * k_col)] + orig[i_col - 2L + 32L * (j_col + 2L + 32L * k_col)] + 
          orig[i_col + 32L * (j_col + 2L + 1L + 32L * k_col)] + orig[i_col + 32L * (j_col + 2L - 1L + 32L * k_col)] + 
          orig[i_col + 32L * (j_col - 1L + 2L + 32L * k_col)] + orig[i_col + 32L * (j_col + 1L - 1L + 32L * k_col)] + 
          orig[i_col + 32L * (j_col - 2L + 2L + 32L * k_col)] + orig[i_col + 32L * (j_col + 2L + 2L + 32L * k_col)]);
        sol[i_col + 32L * (j_col + 32L * k_col)] = buf;
      }
=======
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 8; i_col++) {
        buf += orig[i_col + 1 + ((j_col = (k_col << 3) + k) * 392)];
      }
      sol[k_col + ((j_col << 3) + j)] = buf;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32;k++) {...} */
  for (k = 1 + 0; k < 32 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 0; j_col < 8; j_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 8; i++) {
        buf += sol[i + ((j << 3) + (k_col = (j_col << 3) + k)) * 8];
      }
      sol[i_col + ((j_col << 3) + k)] = buf;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}