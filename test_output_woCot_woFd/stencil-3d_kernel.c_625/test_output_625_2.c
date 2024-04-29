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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2; k <= 32 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2; j <= 32 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2; i <= 32 - 2; i++) {
        idx = i + (j + (k * 32)) * 32;
        idx_col = i - 2 + (j + (k * 32)) * 32;
        idx_row = i + (j - 2) * 32;
        t = orig[idx_col] + orig[idx_col + 1] + orig[idx_col + 2] + orig[idx] + orig[idx + 1] + orig[idx + 2] + orig[idx_row] + orig[idx_row + 1] + orig[idx_row + 2];
        sol[idx] = t;
      }
    }
  }
}