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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2; k <= 32 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2; j <= 32 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2; i <= 32 - 2; i++) {
        idx = ((32 * (32 - 2)) * (k - 2)) + ((32 - 2) * (j - 2)) + (i - 2);
        idx_col = ((32 * (32 - 2)) * (k_col - 2)) + ((32 - 2) * (i_col - 2)) + j_col;
        t = (C0 * (orig[idx_col - 1] + orig[idx_col + 1])) + (C1 * (orig[idx_col] + orig[idx_col + 32]));
        sol[idx] = ((-1) * t) / ((C0 + C1) * (32 - 2) * (32 - 2));
      }
    }
    k_col = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 2; j_col <= 32 - 2; j_col++) {
      i_col = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      for (i_col = 2; i_col <= 32 - 2; i_col++) {
        idx_col = ((32 * (32 - 2)) * (k_col - 2)) + ((32 - 2) * (i_col - 2)) + j_col;
        orig[idx_col] = sol[idx_col];
      }
      k_col++;
    }
  }
}