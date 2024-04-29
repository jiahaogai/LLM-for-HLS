Code: ### Parameter alpha:
 - Type: double

### Parameter beta:
 - Type: double

### Parameter C:
 - Type: double[80][80]

### Parameter A:
 - Type: double[80][60]

### Parameter B:
 - Type: double[80][60]

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
//B is NKxNJ
//C is NKxNK
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Parameter alpha:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Parameter alpha:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Parameter’
    1 | ### Parameter alpha:
      |     ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:20: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Parameter alpha:
      |                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: stray ‘##’ in program
    4 | ### Parameter beta:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘#’ in program
    4 | ### Parameter beta:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: stray ‘##’ in program
    7 | ### Parameter C:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:3: error: stray ‘#’ in program
    7 | ### Parameter C:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:1: error: stray ‘##’ in program
   10 | ### Parameter A:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘#’