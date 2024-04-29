#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i < 32L + 1L; i++) {
        k_col = -(32L + 1L);
        i_col = -(32L + 1L);
        idx_col = 0L;
        loopk_col:
/* Standardize from: for(idx_col = 0; idx_col < 32 + 1; idx_col++) {...} */
        for (; idx_col < 32L + 1L; idx_col++) {
          i_col++;
          idx = i_col * (32L + 1L) + k_col;
          t1 = orig[idx] + ((C0 * (orig[idx + (1L + 0L)] + orig[idx + (0L - 1L)])) + (C1 * (orig[idx + (1L + 1L)] + orig[idx + (0L + 1L)] + orig[idx + (0L - 1L)])));
          sol[idx] = t1;
        }
        k_col++;
      }
    }
    k = 32L + 1L - 2L;
  }
  k = 0L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_1:
/* Standardize from: for(k = 0; k < 32 + 1; k++) {...} */
  for (; k < 32L + 1L; k++) {
    j = 0L;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj_1:
/* Standardize from: for(j = 0; j < 32 + 1; j++) {...} */
    for (; j < 32L + 1L; j++) {
      i = 0L;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_1:
/* Standardize from: for(i = 0; i < 32 + 1; i++) {...} */
      for (; i < 32L + 1L; i++) {
        idx = i * (32L + 1L) + j;
        t2 = sol[idx];
        t3 = (((C0 * (t2 + sol[idx + (1L + 0L)])) + (C1 * (sol[idx + (1L + 1L)] + sol[idx + (0L + 1L)]))) + sol[idx + (0L - 1L)]) / ((C0 + C1) * (1L + 2L));
        sol[idx] = t3;
      }
    }
  }
}