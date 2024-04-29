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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
  for (k = 1 + 32L; k-- > 32L + 1L; ) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 32L; j-- > 32L + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i-- > 32L + 1L; ) {
        k_col = 32L * k;
        i_col = 32L * i;
        j_col = 32L * j;
        k_row = 32L * (k - 1L);
        i_row = 32L * (i - 1L);
        j_row = 32L * (j - 1L);
        idx_col = k_col + i_col + j_col;
        idx_row = k_row + i_row + j_row;
        idx = idx_col + idx_row;
        t = (C0 * (orig[idx_col + idx_row + 1L] + orig[idx_col + 1L + idx_row] + orig[idx_col + 1L + idx_row])) + (C1 * (orig[idx_col + idx_row] + orig[idx_col + 1L + idx_row] + orig[idx_col + idx_row + 1L]));
        sol[idx] = t;
      }
    }
  }
}