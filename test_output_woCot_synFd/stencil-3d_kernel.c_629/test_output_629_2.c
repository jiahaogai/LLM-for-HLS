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
  long idx_up;
  long idx_down;
  long idx_prev;
  long idx_next;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2L + 32L - 2L; k > 2L; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loop_j:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2L + 32L - 2L; j > 2L; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2L + 32L - 2L; i > 2L; i--) {
        i_row = i + 2L - 1L;
        j_row = j + 2L - 1L;
        k_row = k + 2L - 1L;
        idx_row = i_row * 32L + j_row * 32L * 39L + k_row;
        idx = idx_row;
        val = orig[idx_row];
        loop_k_col:
        for (k_col = k + 1L; k_col > 1L; k_col--) {
          idx_up = idx_row + 39L * 32L * (k_col - 1L);
          val += C0 * orig[idx_up];
        }
        loop_j_col:
        for (j_col = j + 1L; j_col > 1L; j_col--) {
          idx_up = idx_row + 39L * (j_col - 1L);
          val += C0 * orig[idx_up];
        }
        loop_i_col:
        for (i_col = i + 1L; i_col > 1L; i_col--) {
          idx_up = idx_row - 39L * (i_col - 1L);
          val += C0 * orig[idx_up];
        }
        loop_k_down:
        for (k_col = k - 1L; k_col > 0L; k_col--) {
          idx_down = idx_row + 39L * 32L * (k_col - 1L);
          val += C1 * orig[idx_down];
        }
        loop_j_down:
        for (j_col = j - 1L; j_col > 0L; j_col--) {
          idx_down = idx_row + 39L * (j_col - 1L);
          val += C1 * orig[idx_down];
        }
        loop_i_down:
        for (i_col = i - 1L; i_col > 0L; i_col--) {
          idx_down = idx_row - 39L * (i_col - 1L);
          val += C1 * orig[idx_down];
        }
        sol[idx] = val;
      }
    }
  }
}