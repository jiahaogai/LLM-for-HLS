#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i > 32 + 1; i--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        sum = orig[i_col + (j_col + (k_col + 32 * 32) * 32) * 39304] + orig[i_col + 1 + (j_col + (k_col + 32 * 32) * 32) * 39304] + orig[i_col + (j_col + 1 + (k_col + 32 * 32) * 32) * 39304] + orig[i_col + 1 + (j_col + 1 + (k_col + 32 * 32) * 32) * 39304] + orig[i_col + (j_col + (k_col + 1 + 32 * 32) * 32) * 39304] + orig[i_col + 1 + (j_col + (k_col + 1 + 32 * 32) * 32) * 39304] + orig[i_col + (j_col + 1 + (k_col + 1 + 32 * 32) * 32) * 39304] + orig[i_col + 1 + (j_col + 1 + (k_col + 1 + 32 * 32) * 32) * 39304];
        sol[i_col + (j_col + (k_col + 32 * 32) * 32) * 32768] = (sum + C0) / C1;
      }
    }
  }
}