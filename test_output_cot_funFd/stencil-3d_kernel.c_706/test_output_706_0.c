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
  
#pragma ACCEL TILE FACTOR=auto{1}
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
        k_col = ((32 * k) - 2);
        i_col = ((32 * i) - 2);
        idx = ((k_col * 32) + i_col);
        idx_col = (idx_col + 1);
        t = (((C0 * (orig[idx] + orig[idx + 1] + orig[idx + 32] + orig[idx + 33])) + (C1 * (orig[idx + 1 + 32] + orig[idx_col] + orig[idx_col + 32] + orig[idx_col + 33]))) / (C0 + C1));
        sol[idx_col] = t;
      }
      idx_col = (((32 - 2) * 32) - 2);
    }
    idx_col = 0;
  }
}