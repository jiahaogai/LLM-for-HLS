<<<<<<< HEAD
Code: ### Function Call:

kernel_syr2k(alpha,beta,C,A,B)


### Function Definition:
=======
Code: ### Function Definition:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
<<<<<<< HEAD
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + beta*C,
//A is ROW MAJOR
//B is ROW MAJOR
//C is ROW MAJOR
=======
//TRANSA = 'T'
//TRANSB = 'N'
// => Form C := alpha*A**T*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
=======
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 0; i < 80; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
<<<<<<< HEAD
      for (j = 0; j < 80; j++) {
=======
      for (i = 0; i < 80; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
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
=======
  
#pragma endscop
}
Error: 
Please check the code and try again.
Code: ### Function Definition:
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'T'
// => Form C := alpha*A**T*B**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 0; i < 80; i++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (i = 0; i < 80; i++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
