Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 240; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Disable automatic pipelining for the middle loop.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘`’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Disable automatic pipelining for the middle loop.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Disable automatic pipelining for the middle loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:37: error: stray ‘`’ in program
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Disable automatic pipelining for the middle loop.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:38: error: expected identifier or ‘(’ before ‘:’ token
    2 | - `#pragma ACCEL PIPELINE auto{off}`: Disable automatic pipelining for the middle loop.
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{2}`: Decompose the middle loop into two tiles, each of which is processed in parallel.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{2}`: Decompose the middle loop into two tiles, each of which is processed in parallel.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:37: error: stray ‘`’ in program
    3 | - `#pragma ACCEL TILE FACTOR=auto{2}`: Decompose the middle loop into two tiles, each of which is processed in parallel.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c