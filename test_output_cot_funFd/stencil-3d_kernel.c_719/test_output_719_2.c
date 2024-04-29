#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k_col:
/* Standardize from: for(k_col = 1; k_col < 40; k_col++) {...} */
  for (k_col = 16L; k_col <= 384L; k_col += 16L) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 40; j_col++) {...} */
    for (j_col = 16L; j_col <= 384L; j_col += 16L) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_col:
/* Standardize from: for(i_col = 1; i_col < 40; i_col++) {...} */
      for (i_col = 16L; i_col <= 384L; i_col += 16L) {
        idx_col = (40L + 2L) * (40L + 2L) * (k_col - 1L) + (40L + 2L) * (j_col - 1L) + i_col - 1L;
        t = (((C0 * (orig[idx_col - 1L] + orig[idx_col + 1L])) + (C1 * (orig[idx_col - 40L] + orig[idx_col + 40L]))) - orig[idx_col]) / (C0 + C1);
        sol[idx_col] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k_row:
/* Standardize from: for(k_row = 1; k_row < 40 - 2; k_row++) {...} */
  for (k_row = 16L; k_row <= 380L; k_row += 16L) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_row:
/* Standardize from: for(j_row = 1; j_row < 40 - 2; j_row++) {...} */
    for (j_row = 16L; j_row <= 376L; j_row += 16L) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_row:
/* Standardize from: for(i_row = 1; i_row < 40 - 2; i_row++) {...} */
      for (i_row = 16L; i_row <= 372L; i_row += 16L) {
        idx_row = (40L + 2L) * (k_row - 1L) + (j_row - 1L) + i_row - 1L;
        t = (((C0 * (sol[idx_row - 1L] + sol[idx_row + 1L])) + (C1 * (sol[idx_row - 40L] + sol[idx_row + 40L]))) - sol[idx_row]) / (C0 + C1);
        idx = idx_row;
        sol[idx] = t;
      }
    }
  }
}