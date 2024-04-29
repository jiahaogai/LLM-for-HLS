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
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j <= 392 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk_col:
    for (k_col = 0; k_col < 16; k_col++) {
      i_col = 1 + k_col * 4;
      idx_col = i_col * 392 + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i <= 390 - 1; i++) {
        idx = i * 392 + j;
        t = orig[idx_col] + 3 * (orig[idx - 1] + orig[idx + 1] - 2 * orig[idx]) + orig[idx_col + 392] - orig[idx_col - 392];
        sol[idx] = t;
        idx_col++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
  for (k = 1; k <= 392 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
    for (j_col = 0; j_col < 16; j_col++) {
      i_col = 1 + j_col * 4;
      idx_col = i_col * 392 + k;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i <= 390 - 1; i++) {
        idx = i * 392 + k;
        t = sol[idx_col] + 3 * (sol[idx - 392] + sol[idx + 392] - 2 * sol[idx]) + orig[idx];
        sol[idx] = (t + 8) / 16;
        idx_col++;
      }
    }
  }
}