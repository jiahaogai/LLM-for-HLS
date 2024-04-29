#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      k_col = k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1; i++) {
        i_col = i;
        idx = i + (32 + 1) * (k + (32 + 1) * j);
        idx_col = i_col + (32 + 1) * (k_col + (32 + 1) * j);
        sol[idx] = ((C0 * orig[idx_col]) + (C1 * (orig[idx_col + (32 + 1) * 1] + orig[idx_col + (32 + 1) * 2] + orig[idx_col + (32 + 1) * 3] + orig[idx_col + (32 + 1) * 4] + orig[idx_col + (32 + 1) * 5] + orig[idx_col + (32 + 1) * 6] + orig[idx_col + (32 + 1) * 7] + orig[idx_col + (32 + 1) * 8] + orig[idx_col + (32 + 1) * 9] + orig[idx_col + (32 + 1) * 10] + orig[idx_col + (32 + 1) * 11] + orig[idx_col + (32 + 1) * 12] + orig[idx_col + (32 + 1) * 13] + orig[idx_col + (32 + 1) * 14] + orig[idx_col + (32 + 1) * 15] + orig[idx_col + (32 + 1) * 16] + orig[idx_col + (32 + 1) * 17] + orig[idx_col + (32 + 1) * 18] + orig[idx_col + (32 + 1) * 19] + orig[idx_col + (32 + 1) * 20] + orig[idx_col + (32 + 1) * 21] + orig[idx_col + (32 + 1) * 22] + orig[idx_col + (32 + 1) * 23] + orig[idx_col + (32 + 1) * 24] + orig[idx_col + (32 + 1) * 25] + orig[idx_col + (32 + 1) * 26] + orig[idx_col + (32 + 1) * 27] + orig[idx_col + (32 + 1) * 28] + orig[idx_col + (32 + 1) * 29] + orig[idx_col + (32 + 1) * 30] + orig[idx_col + (32 + 1) * 31])) / (C0 + C1);
      }
    }
  }
}