<<<<<<< HEAD
Code: ### Flat Contraction:
   C := alpha*A*B**T + beta*C,

### PIPELINE auto{}
  
### TILE FACTOR=auto{1}
  
### SPECULATE FACTOR=auto{1}
  
### ACCEL PARALLEL FACTOR=auto{16}
   
### ACCEL PIPELINE auto{}
   
### ACCEL TILE FACTOR=auto{1}
   
### ACCEL PARALLEL FACTOR=auto{8}
 
#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*B**T + beta*C,
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
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Flat Contraction:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Flat Contraction:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Flat’
    1 | ### Flat Contraction:
      |     ^~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:21: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Flat Contraction:
      |                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: stray ‘##’ in program
    4 | ### PIPELINE auto{}
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘#’ in program
    4 | ### PIPELINE auto{}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: stray ‘##’ in program
    6 | ### TILE FACTOR=auto{1}
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:3: error: stray ‘#’ in program
    6 | ### TILE FACT
=======
Summary: 
Please check the code and try again.
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
