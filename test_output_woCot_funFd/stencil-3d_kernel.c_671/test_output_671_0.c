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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k < 40L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j < 40L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i < 40L; i++) {
        i_row = 40L * (0L - 1L) + i;
        j_row = 40L * (j - 1L);
        k_row = 40L * (k - 1L);
        idx_row = i_row * 40L + j_row;
        loop_k_col:
/* Standardize from: for(k_col = 0; k_col < 40; k_col++) {...} */
        for (k_col = 0L; k_col < 40L; k_col++) {
          k_idx = 40L * (k_col - 1L);
          j_idx = 40L * (j - 1L);
          i_idx = 40L * (i - 1L);
          idx_col = k_idx + j_idx + i_idx;
          idx = idx_row + k_idx;
          t = orig[idx_col] + orig[idx_row + j_idx] + orig[idx_row + i_idx] + orig[idx_col + 1L] + orig[idx_row + j_idx + 1L] + orig[idx_row + i_idx + 1L] + orig[idx_col + 40L] + orig[idx_row + j_idx + 40L] + orig[idx_row + i_idx + 40L] + orig[idx_col + 40L + 1L] + orig[idx_row + j_idx + 40L + 1L] + orig[idx_row + i_idx + 40L + 1L];
          sol[idx] = t;
        }
      }
    }
  }
}