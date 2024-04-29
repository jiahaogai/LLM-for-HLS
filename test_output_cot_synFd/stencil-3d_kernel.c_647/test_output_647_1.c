#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_slash;
  long idx_backslash;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1 + 0; i < 33 + 0; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1 + 0; j < 33 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1 + 0; k < 33 + 0; k++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        i_row = i + 1;
        j_row = j + 1;
        k_row = k + 1;
        idx_col = i_col * 32 * 32 + j_col * 32 + k_col;
        idx_row = i_row * 32 * 32 + j_row * 32 + k_row;
        idx_slash = i_col * 31 * 32 + j_col * 32 + k_row;
        idx_backslash = i_row * 31 * 32 + j_row * 32 + k_col;
        sum = ((orig[idx_col] + orig[idx_row]) + orig[idx_slash]) + orig[idx_backslash];
        idx = i * 32 * 32 + j * 32 + k;
        sol[idx] = sum;
      }
    }
  }
}