Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANS = 'N'
//UPLO = 'L'
//N = 80
//M = 60
//ALPHA = 1
//BETA = 0
//LEN = 4800
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘`’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:37: error: stray ‘`’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:38: error: expected identifier or ‘(’ before ‘:’ token
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:41: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{1}`: