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
    loopk_col:
    for (k_col = 1 + 32 - 1; k_col < 32 + 1; k_col++) {
      i_col = 1 + 32 - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
      while (i_col <= 32 + 1 - 3) {
        idx_col = (k_col - 1) * (32 + 1) * (32 + 1) + (i_col - 1) * (32 + 1) + j - 1;
        t = orig[idx_col] + 32L * 32L * C0 * (orig[idx_col + 32L] + orig[idx_col + 32L * (32L + 1)]);
        idx = (k - 1) * (32 + 1) * (32 + 1) + (i - 1) * (32 + 1) + j;
        sol[idx] = t;
        i_col++;
        idx_col++;
      }
    }
  }
}