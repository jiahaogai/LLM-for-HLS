#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
  for (j = 1; j <= 39 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
    for (k = 1; k <= 39 - 1; k++) {
      k_col = 40 * k;
      i_col = 40 * j;
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
      for (i = 1; i <= 39 - 1; i++) {
        idx = i + i_col;
        idx_col = idx + k_col;
        C0_idx = idx_col - 1;
        C1_idx = idx_col + 1;
        sum = C0 * orig[C0_idx] + C1 * (orig[idx_col] + orig[C1_idx]);
        sol[idx] = sum;
      }
    }
  }
}