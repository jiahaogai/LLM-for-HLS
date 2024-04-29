Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
<<<<<<< HEAD
//A is A(80,60)
//C is C(80,80)
=======
//A is NIxNK
//C is NIxNJ
//K is NK
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{80}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{5}
=======
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
<<<<<<< HEAD
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - #pragma ACCEL PARALLEL FACTOR=auto{1}: Limit the number of C array writes to one per cycle.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘#’ in program
    2 | - #pragma ACCEL PARALLEL FACTOR=auto{1}: Limit the number of C array writes to one per cycle.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:40: error: expected identifier or ‘(’ before ‘:’ token
    2 | - #pragma ACCEL PARALLEL FACTOR=auto{1}: Limit the number of C array writes to one per cycle.
      |                                        ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘#’ in program
    3 | - #pragma ACCEL PARALLEL FACTOR=auto{4}: Allow 4 C array reads per cycle.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:40: error: expected identifier or ‘(’ before ‘:’ token
    3 | - #pragma ACCEL PARALLEL FACTOR=auto{4}: Allow 4 C array reads per cycle.
      |                                        ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘#’ in program
    4 | - #pragma ACCEL PARALLEL FACTOR=auto{1}: Limit the number of A array reads to one per cycle.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:40: error: expected identifier or ‘(’ before ‘:’ token
    4 | - #pragma ACCEL PARALLEL FACTOR=auto{1}: Limit the number of A array reads to one per cycle.
      |                                        ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: error: stray ‘#’ in program
    5 | - #pragma ACCEL PARAL
=======
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
