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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k <= 39L - 1L; k += 1L) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j <= 39L - 1L; j += 1L) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i <= 39L - 1L; i += 1L) {
        i_row = i + 1L;
        if (i_row == 40L) {
          i_row = 0L;
        }
        i_col = i + 1L;
        if (i_col == 40L) {
          i_col = 0L;
        }
        j_row = j + 1L;
        if (j_row == 40L) {
          j_row = 0L;
        }
        j_col = j + 1L;
        if (j_col == 40L) {
          j_col = 0L;
        }
        k_row = k + 1L;
        if (k_row == 40L) {
          k_row = 0L;
        }
        k_col = k + 1L;
        if (k_col == 40L) {
          k_col = 0L;
        }
        idx = i + (j + (k * 40L)) * 40L;
        idx_col = i_col + (j_col + (k_col * 40L)) * 40L;
        idx_row = i_row + (j_row + (k_row * 40L)) * 40L;
        t = orig[idx] + ((orig[idx_col] + orig[idx_row]) / 2L);
        sol[idx] = t;
      }
    }
  }
}