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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 16L; i--) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        i_col = ((32L + 1L) * (32L + 1L)) * i;
        idx = i_col + j + k_col;
        idx_col = i_col + j - 1L + k_col;
        t = orig[idx_col] + orig[idx_col + 1L] + orig[idx_col + 32L + 1L] + orig[idx_col + 32L] + orig[idx_col - 32L] + orig[idx_col - 32L + 1L] + orig[idx_col - 1L];
        sol[idx] = t;
      }
    }
  }
}