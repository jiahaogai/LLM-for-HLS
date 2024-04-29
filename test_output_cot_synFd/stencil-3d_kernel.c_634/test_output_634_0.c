#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
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
  long mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2; k <= 32 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2; j <= 32 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2; i <= 32 - 2; i++) {
        i_row = 32 * (1 + k) + i;
        j_row = 32 * (1 + j);
        k_row = 32 * (1 + k);
        i_col = 32 * (1 + i);
        j_col = 32 * (1 + j);
        k_col = 32 * (1 + k);
        idx_col = i_col + j_col + k_col;
        idx_row = i_row + j_row + k_row;
        mult = (-1 * C0 * orig[idx_row]) + (C1 * (orig[idx_col] + orig[idx_col + 1] + orig[idx_col + 32] + orig[idx_col + 32 + 1] + orig[idx_col + 32 + 32] + orig[idx_col + 32 + 32 + 1]));
        sol[idx_row] = mult + orig[idx_row];
      }
    }
  }
}