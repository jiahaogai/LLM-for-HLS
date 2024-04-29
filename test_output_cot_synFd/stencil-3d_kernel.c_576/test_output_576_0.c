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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_row = i + 1L - 1L;
        j_row = j + 1L - 1L;
        k_row = k + 1L - 1L;
        i_col = i + 32L - 1L;
        j_col = j + 32L - 1L;
        k_col = k + 32L - 1L;
        idx_in = i_col + ((j_col) + (k_col) * 32L) * 39L;
        t = orig[idx_in];
        idx_row = i_row + ((j_row) + (k_row) * 32L) * 32L;
        loop_k_col:
        for (k_col = 0L; k_col < 1L; k_col++) {
          loop_j_col:
          for (j_col = 0L; j_col < 1L; j_col++) {
            idx_col = i_col + (j_col + k_col * 1L) * 32L;
            sol[idx_row + k_col * 1L * 32L] = t - 1L * ((((0L + 0L * 32L) + 1L * 32L) * 39L) + ((0L + 1L * 32L) + 0L * 32L) * 32L) * orig[idx_col];
          }
        }
      }
    }
  }
}