Code: ### Flat

 #pragma ACCEL kernel

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
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Flat
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Flat
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:9: error: expected ‘;’ before ‘void’
    1 | ### Flat
      |         ^
      |         ;
......
    5 | void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
      | ~~~~     

Please check the code and try again.
Code: ### Flat

 #pragma ACCEL kernel

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
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {