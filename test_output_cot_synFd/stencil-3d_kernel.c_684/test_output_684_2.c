Code: #pragma ACCEL kernel

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
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 32; j-- > 32 + 1; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32; i-- > 32 + 1; ) {
        idx = i + (j + (k * 32)) * 32;
        idx_col = i - 1 + (j + (k * 32)) * 32;
        idx_row = i + (j - 1 + (k * 32)) * 32;
        idx_k_col = i + (j + ((k - 1) * 32)) * 32;
        idx_k_row = i + (j + ((k + 1) * 32)) * 32;
        t = orig[idx] + C0 * (orig[idx_col] + orig[idx_row] + orig[idx_k_col] + orig[idx_k_row]);
        sol[idx] = t;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:42:9: error: ‘idx_k_col’ undeclared (first use in this function); did you mean ‘idx_col’?
   42 |         idx_k_col = i + (j + ((k - 1) * 32)) * 32;
      |         ^~~~~~~~~
      |         idx_col
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:42:9: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:43:9: error: ‘idx_k_row’ undeclared (first use in this function); did you mean ‘idx_row’?
   43 |         idx_k_row = i + (j + ((k + 1) * 32)) * 32;
      |         ^~~~~~~~~
      |         idx_row

Please check the code and try again.
Code: #pragma ACCEL kernel

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
  long idx