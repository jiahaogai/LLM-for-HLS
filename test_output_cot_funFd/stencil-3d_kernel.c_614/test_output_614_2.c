Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32 - 1; i++) {...} */
  for (i = 1 + 32 - 1; 1 < i; i--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loop_j:
/* Standardize from: for(j = 1; j < 32 - 1; j++) {...} */
    for (j = 1 + 32 - 1; 1 < j; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32 - 1; k++) {...} */
      for (k = 1 + 32 - 1; 1 < k; k--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        t = ((((orig[i_col + 39073 * j_col] + orig[i_col + 1 + 39073 * j_col]) + orig[i_col + 39073 * j_col + 1]) + orig[i_col + 39073 * (j_col + 1)]) + orig[i_col + 1 + 39073 * (j_col + 1)]) + orig[i_col + 1 + 39073 * j_col + 1];
        sol[i + 32768 * j + 4096 * k] = ((t + orig[i_col + 39073 * j_col + 4096]) / 4);
      }
    }
  }
}