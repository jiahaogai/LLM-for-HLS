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
  loopk:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k < 40L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loopj:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j < 40L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i < 40L; i++) {
        idx = ((40L * 40L) * k) + (40L * j) + i;
        idx_col = ((40L - 1L) * 40L) + 40L - 1L;
        idx_row = (40L - 1L);
        t = orig[idx] / 2L;
        sol[idx] = t;
        loopk_col:
/* Standardize from: for(k_col = 1; k_col < 40; k_col++) {...} */
        for (k_col = 1L; k_col < 40L; k_col++) {
          k_row = 40L - k_col;
          i_col = 40L - 1L;
          i_row = i + k_row;
          if (i_row >= 0L) {
            if (i_row < 40L) {
              idx_in = (40L * k_row) + i_col;
              sol[idx] += t * orig[idx_in];
            }
          }
        }
        loopj_col:
/* Standardize from: for(j_col = 1; j_col < 40; j_col++) {...} */
        for (j_col = 1L; j_col < 40L; j_col++) {
          j_row = 40L - j_col;
          i_col = i + j_row;
          if (i_col >= 0L) {
            if (i_col < 40L) {
              idx_in = (40L * j_row) + i_col;
              sol[idx] += t * orig[idx_in];
            }
          }
        }
        loopk_row:
/* Standardize from: for(k_row = 1; k_row < 40; k_row++) {...} */
        for (k_row = 1L; k_row < 40L; k_row++) {
          k_col = 40L - k_row;
          i_col = 40L - 1L;
          i_row = i + k_col;
          if (i_row >= 0L) {
            if (i_row < 40L) {
              idx_in = (40L * k_col) + i_col;
              sol[idx] += t * orig[idx_in];
            }
          }
        }
        loopj_row:
/* Standardize from: for(j_row = 1; j_row < 40; j_row++) {...} */
        for (j_row = 1L; j_row < 40L; j_row++) {
          j_col = 40L - j_row;
          i_col = i + j_col;
          if (i_col >= 0L) {
            if (i_col < 40L) {
              idx_in = (40L * j_col) + i_col;
              sol[idx] += t * orig[idx_in];
            }
          }
        }
      }
    }
  }
}