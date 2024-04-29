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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
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
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | 11. `#pragma ACCEL PIPELINE auto{off}`: Disable pipelining for the loops.
      | ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:5: error: stray ‘`’ in program
    2 | 11. `#pragma ACCEL PIPELINE auto{off}`: Disable pipelining for the loops.
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:6: error: stray ‘#’ in program
    2 | 11. `#pragma ACCEL PIPELINE auto{off}`: Disable pipelining for the loops.
      |      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:38: error: stray ‘`’ in program
    2 | 11. `#pragma ACCEL PIPELINE auto{off}`: Disable pipelining for the loops.
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:39: error: expected identifier or ‘(’ before ‘:’ token
    2 | 11. `#pragma ACCEL PIPELINE auto{off}`: Disable pipelining for the loops.
      |                                       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:5: error: stray ‘`’ in program
    3 | 12. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loops whole, without dividing them into smaller parts, with a tile factor of 1.
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:6: error: stray ‘#’ in program
    3 | 12. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loops whole, without dividing them into smaller parts, with a tile factor of 1.
      |      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:39: error: stray ‘`’ in program