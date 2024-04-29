#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

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
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
  for (j = 1; j <= 39; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
    for (k = 1; k <= 39; k++) {
      k_col = 40 * k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 40;i++) {...} */
      for (i = 1; i <= 39; i++) {
        i_col = 40 * i;
        idx = i_col + k_col;
        idx_col = k_col + i_col;
        C0_idx = idx_col - 40;
        C1_idx = idx_col + 40;
        tmp = C0 * (orig[C0_idx + 1] + orig[C0_idx + 40] + orig[C0_idx + 40 * 2] + orig[C0_idx + 40 * 3] - 4.0 * orig[C0_idx]) + C1 * (orig[C1_idx + 1] + orig[C1_idx + 40] + orig[C1_idx + 40 * 2] + orig[C1_idx + 40 * 3] - 4.0 * orig[C1_idx]) - orig[idx];
        sol[idx] = tmp;
      }
    }
  }
}