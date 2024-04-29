#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_row = 40L * (i - 1L);
        j_row = 40L * (j - 1L);
        k_row = 40L * (k - 1L);
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        idx_col = i_col + 40L * j_col + 1600L * k_col;
        idx_row = i_row + 40L * j_row + 1600L * k_row;
        sum0 = orig[idx_col + 1600L] + orig[idx_col + 32L + 1600L] + orig[idx_col + 16L + 32L + 1600L] + orig[idx_col + 32L + 16L + 32L + 1600L];
        sum1 = orig[idx_col + 4L + 1600L] + orig[idx_col + 36L + 1600L] + orig[idx_col + 12L + 32L + 1600L] + orig[idx_col + 36L + 16L + 32L + 1600L] + orig[idx_col + 12L + 16L + 32L + 1600L] + orig[idx_col + 28L + 16L + 32L + 1600L] + orig[idx_col + 24L + 32L + 1600L];
        mul0 = sum0 * 32L;
        mul1 = sum1 * 32L;
        sol[idx_row] = mul0 + mul1;
      }
    }
  }
}