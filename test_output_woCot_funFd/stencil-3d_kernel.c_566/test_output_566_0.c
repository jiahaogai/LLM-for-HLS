#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
<<<<<<< HEAD
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
=======
  long j_col;
  long i_col;
  long bound;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
    for (j_col = 1; j_col < 40; j_col++) {
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        idx_col = (((i_col - 1) * 40) + (j_col - 1)) * 40 + (k_col - 1);
        sum0 = orig[idx_col];
        mul0 = sum0 * 3;
        i = 0;
        loopk_row:
/* Standardize from: for(k_row = 0;k_row < 40;k_row++) {...} */
        for (k_row = 0; k_row < 40; k_row++) {
          j = 0;
          loopj_row:
/* Standardize from: for(j_row = 0;j_row < 40;j_row++) {...} */
          for (j_row = 0; j_row < 40; j_row++) {
            i = 0;
            loopi:
/* Standardize from: for(i = 0;i < 40;i++) {...} */
            for (i = 0; i < 40; i++) {
              idx_row = (((i - 1) * 40) + (j_row - 1)) * 40 + (k_row - 1);
              idx = (((i - 1) * 40) + (j - 1)) * 40 + (k - 1);
              sum1 = orig[idx_row] + mul0 - orig[idx];
              mul1 = sum1 * 2;
              sol[idx] = mul1;
            }
            j++;
          }
          k++;
        }
        i_col++;
      }
      j_col++;
    }
    k_col++;
=======
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 2; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 1; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        bound = (32L * 32L) * (k - 1L);
        sum0 = orig[bound + j_col * 32L + i_col] + orig[bound + j_col * 32L + i_col + 1L] + orig[bound + (j_col + 1L) * 32L + i_col] + orig[bound + (j_col + 1L) * 32L + i_col + 1L];
        sum1 = orig[bound + (j_col + 2L) * 32L + i_col] + orig[bound + (j_col + 2L) * 32L + i_col + 1L];
        mul0 = sum0 * 32L;
        mul1 = sum1 * 1L;
        sol[bound + j_col * 32L + i_col] = mul0 + mul1;
      }
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}