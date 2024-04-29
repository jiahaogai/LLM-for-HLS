#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 18; k <= 39300L - 18; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 2; j < 393; j++) {...} */
    for (j = 18; j <= 393 - 18; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 393; i++) {...} */
      for (i = 18; i <= 393 - 18; i++) {
        idx = (39304 * k) + (393 * j) + i;
        idx_col = (39304 * (k - 18)) + (393 * (j - 18)) + (i - 18);
        t = ((C0 * (orig[idx_col - 39304] + orig[idx_col - 393] + orig[idx_col + 393] + orig[idx_col + 39304])) + (C1 * (orig[idx_col - 1] + orig[idx] + orig[idx + 393] + orig[idx + 39304]))) / 8;
        sol[idx] = t;
      }
    }
  }
}