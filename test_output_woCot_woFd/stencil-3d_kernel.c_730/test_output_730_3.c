#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long kj;
  long i_col;
  long j_col;
  long k_col;
  long idx;
  long idx_col;
  long t1;
  long t2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
  for (j = 1; j <= 32; j++) {
    long j_col = j - 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
    for (k = 1; k <= 32; k++) {
      long k_col = k - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
      for (i = 1; i <= 32; i++) {
        long i_col = i - 1;
        idx = i + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        idx_col = i_col + ((j_col - 1) * 32) + ((k_col - 1) * 32 * 32);
        t1 = orig[idx] + ((C0 * (orig[idx_col + 1] + orig[idx_col - 1])) + (C1 * (orig[idx_col + 32] + orig[idx_col - 32])));
        t2 = orig[idx] + ((C0 * (orig[idx_col + 32] + orig[idx_col - 32])) + (C1 * (orig[idx_col + 32 * 2] + orig[idx_col - 32 * 2])));
        sol[idx] = t1 + ((- 1L) * t2);
      }
    }
  }
}