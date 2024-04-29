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
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
  for (i = 0L; i <= 39L - 1L; i += 1L) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j <= 39L - 1L; j += 1L) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
      for (k = 0L; k <= 39L - 1L; k += 1L) {
        k_col = ((40L * k) + j) + i;
        j_col = (40L * j) + i;
        i_col = (40L * i) + j;
        idx = (40L * k) + j;
        idx_col = (40L * j) + k;
        t = orig[i_col] + orig[j_col] + orig[k_col];
        t -= (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx + 1] + orig[idx - 1]);
        sol[idx] = t;
      }
    }
  }
}