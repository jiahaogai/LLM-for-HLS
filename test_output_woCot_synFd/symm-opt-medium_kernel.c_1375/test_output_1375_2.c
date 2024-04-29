Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 240; j++) {
        C[i][j] += alpha * A[k][i] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - `C[i][j] *= beta`: 
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘`’ in program
    2 | - `C[i][j] *= beta`: 
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:19: error: stray ‘`’ in program
    2 | - `C[i][j] *= beta`: 
      |                   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:3: error: stray ‘`’ in program
    6 | - `C[i][j] += alpha * temp1`: 
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:28: error: stray ‘`’ in program
    6 | - `C[i][j] += alpha * temp1`: 
      |                            ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘`’ in program
   10 | - `temp2 += A[i][k] * B[k][j]`: 
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:30: error: stray ‘`’ in program
   10 | - `temp2 += A[i][k] * B[k][j]`: 
      |                              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:14:3: error: stray ‘`’ in program
   14 | - `temp1 += A[k][i] * temp2`: 
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:14:28: error: stray ‘`’ in program
   14 | - `temp1 += A[k][i] * temp2`: 
      |                            ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;