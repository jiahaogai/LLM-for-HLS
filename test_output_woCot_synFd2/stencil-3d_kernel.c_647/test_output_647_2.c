#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long kf;
  long jf;
  long if_;
  long i_row;
  long j_row;
  long k_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
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
        idx_col = i_col * 33 + j_col * 32 + k_col;
        i_row = i - 1 + 32;
        j_row = j - 1 + 32;
        k_row = k - 1 + 32;
        idx_row = i_row * 33 + j_row * 32 + k_row;
        t = C0 * (orig[idx_col] + orig[idx_row]) + C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_row + 1] + orig[idx_row - 1] + orig[idx_row + 32] + orig[idx_row - 32] + orig[idx_col + 32] + orig[idx_col - 32]);
        sol[idx_row + 32 * 33] = t;
      }
    }
    loop_kf:
/* Standardize from: for(kf = 30; kf >= 0; kf--) {...} */
    for (kf = 30 + 0; kf >= 0 + 0; kf--) {
      loop_jf:
/* Standardize from: for(jf = 30; jf >= 0; jf--) {...} */
      for (jf = 30 + 0; jf >= 0 + 0; jf--) {
        loop_if:
/* Standardize from: for(if_ = 30; if_ >= 0; if_--) {...} */
        for (if_ = 30 + 0; if_ >= 0 + 0; if_--) {
          k = kf + 1;
          j = jf + 1;
          i = if_ + 1;
          idx_row = i * 33 * 32 + j * 32 + k;
          sol[idx_row] = ((2 * sol[idx_row]) + orig[idx_row]) / 3.0;
        }
      }
    }
  }
}