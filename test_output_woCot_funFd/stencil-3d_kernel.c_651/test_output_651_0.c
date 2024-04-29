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
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i < 32 + 1L; i++) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        buf = 0;
        k_col = (k - 1) * 32;
        j_col = (j - 1) * 32;
        i_col = (i - 1) * 32;
        loopk_col:
/* Standardize from: for(k_col = (k - 1) * 32; k_col < (k - 1) * 32 + 32 && k_col < 32; k_col++) {...} */
        for (k_col = (k - 1) * 32; k_col < (k - 1) * 32 + 32L && k_col < 32L; k_col++) {
          loopj_col:
/* Standardize from: for(j_col = (j - 1) * 32; j_col < (j - 1) * 32 + 32 && j_col < 32; j_col++) {...} */
          for (j_col = (j - 1) * 32; j_col < (j - 1) * 32 + 32L && j_col < 32L; j_col++) {
            loopi_col:
/* Standardize from: for(i_col = (i - 1) * 32; i_col < (i - 1) * 32 + 32 && i_col < 32; i_col++) {...} */
            for (i_col = (i - 1) * 32; i_col < (i - 1) * 32 + 32L && i_col < 32L; i_col++) {
              buf += orig[i_col + j_col * 32 + k_col * 32 * 32] * C0;
            }
          }
        }
        sol[idx] = buf;
      }
    }
  }
}