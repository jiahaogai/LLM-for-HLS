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
  long idx_orig;
  long idx_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        i_row = i - 1;
        j_row = j - 1;
        k_row = k - 1;
        i_col = i + 0;
        j_col = j + 0;
        k_col = k + 0;
        idx_orig = i_row * (32 + 1) * (32 + 1) + j_row * (32 + 1) + k_row;
        idx_sol = i_col * (32 + 1) * (32 + 1) + j_col * (32 + 1) + k_col;
        idx = idx_orig;
        orig[idx] = sol[idx_sol];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k_col:
/* Standardize from: for(k_col = 32 + 1; k_col > 0 + 0; k_col--) {...} */
    for (k_col = 32 + 1; k_col > 0 + 0; k_col--) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_j_col:
/* Standardize from: for(j_col = 32 + 1; j_col > 0 + 0; j_col--) {...} */
      for (j_col = 32 + 1; j_col > 0 + 0; j_col--) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_i_col:
/* Standardize from: for(i_col = 32 + 1; i_col > 0 + 0; i_col--) {...} */
        for (i_col = 32 + 1; i_col > 0 + 0; i_col--) {
          i_row = i_col - 1;
          j_row = j_col - 1;
          k_row = k_col - 1;
          i = i_row;
          j = j_row;
          k = k_row;
          idx_sol = i_col * (32 + 1) * (32 + 1) + j_col * (32 + 1) + k_col;
          idx = i_row * (32 + 1) * (32 + 1) + j_row * (32 + 1) + k_row;
          sol[idx_sol] = ((2 * orig[idx]) + (orig[idx + (32 + 1) * (32 + 1)] ) + (orig[idx + (32 + 1)] ) + (orig[idx + 1] ) + (orig[idx + (32 + 1) * (32 + 1) + 1] ) + (orig[idx + (32 + 1) + 1] ) + (orig[idx + 1 + (32 + 1)] ) + (orig[idx + 1 + 1] )) / 8.0;
        }
      }
    }
  }
}