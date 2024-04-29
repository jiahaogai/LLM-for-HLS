Code: ### Generated Code:
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
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1l; i <= 32l; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1l; j <= 32l; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1l; k <= 32l; k++) {
        sum = 0.0l;
        i_col = (i - 1l) * 32l + 1l;
        j_col = (j - 1l) * 32l + 1l;
        k_col = (k - 1l) * 1l;
        loop_k_col:
/* Standardize from: for(idx_col = 0; idx_col < 32 * 32; idx_col++) {...} */
        for (idx_col = 0l; idx_col < 32l * 32l; idx_col++) {
          idx_in = i_col + idx_col / 32l;
          idx_row = j_col + idx_col % 32l;
          idx = idx_in * 32l * 32l + idx_row * 32l + k_col;
          sum += orig[idx] * C1;
        }
        sol[i][j][k] = sum;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: ### Generated Code:
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
  long idx_prev;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1l; i <= 32l; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1l; j <= 32l; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}