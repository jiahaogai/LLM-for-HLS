Code: #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: stray ‘##’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘##’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
      |   ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:37: error: stray ‘##’ in program
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
      |                                     ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:38: error: expected identifier or ‘(’ before ‘:’ token
    2 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole, without dividing it into smaller parts
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘##’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{10}`: Execute loop iterations concurrently in groups of 10
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL PARALLEL FACTOR=auto{10}`: Execute loop iterations concurrently in groups of 10
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:42: error: stray ‘##’ in program