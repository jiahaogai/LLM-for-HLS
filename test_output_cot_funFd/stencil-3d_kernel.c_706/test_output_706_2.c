#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2;; k++) {
    if (((long )39302) <= k) {
      break;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 39302; j++) {...} */
    for (j = 2;; j++) {
      if (((long )39302) <= j) {
        break;
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 39302; i++) {...} */
      for (i = 2;; i++) {
        if (((long )39302) <= i) {
          break;
        }
        idx = ((k * 39302) + j) * 39302 + i;
        idx_col = ((k - 1) * 39302 + j - 1) * 39302 + i - 1;
        t = C0 * orig[idx] + C1 * (orig[idx_col] + orig[idx_col + 1] + orig[idx_col + 39302] + orig[idx_col + 39304]);
        sol[idx] = t;
      }
    }
    k_col = 1 + ((k - 2) * 39302);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_col:
/* Standardize from: for(j = 2; j < 39302; j++) {...} */
    for (j = 2;; j++) {
      if (((long )39302) <= j) {
        break;
      }
      i_col = 1 + ((j - 2) * 39302);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_col:
/* Standardize from: for(i = 2; i < 39302; i++) {...} */
      for (i = 2;; i++) {
        if (((long )39302) <= i) {
          break;
        }
        idx_col = i_col + k_col;
        orig[idx_col] = sol[idx_col];
      }
    }
  }
}