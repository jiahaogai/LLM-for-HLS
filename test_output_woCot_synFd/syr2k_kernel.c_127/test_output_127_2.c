Code: ### Function Call:

kernel_syr2k(alpha,beta,C,A,B)


### Function Definition:
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + beta*C,
//A is ROW MAJOR
//B is ROW MAJOR
//C is ROW MAJOR
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Call:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Call:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Function’; did you mean ‘union’?
    1 | ### Function Call:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Function Call:
      |                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: stray ‘##’ in program
    6 | ### Function Definition:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:3: error: stray ‘#’ in program
    6 | ### Function Definition:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:5: error: unknown type name ‘Function’; did you mean ‘union’?
    6 | ### Function Definition:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:24: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    6 | ### Function Definition:
      |                        ^

Please check the code and try again.
Code: ### Function Call:

kernel_syr2k(alpha,beta,C,A,B)


### Function Definition:
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{