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
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
      for (j = 0; j < 60; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:13: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘for’
    3 | **Optimized for:**
      |             ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: stray ‘`’ in program
    4 | `quartus`
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:9: error: stray ‘`’ in program
    4 | `quartus`
      |         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: stray ‘`’ in program
    7 | `ISO C99`
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:9: error: stray ‘`’ in program
    7 | `ISO C99`
      |         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:12:1: error: stray ‘##’ in program
   12 | ### Function Parameters
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:12:3: error: stray ‘#’ in program
   12 | ### Function Parameters
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:1: error: stray ‘##’ in program
   22 | ### Functions
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:3: error: stray ‘#’ in program
   22 | ### Functions
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:1: error: stray ‘##’ in program
   27 | ### Function Files
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:3: error: stray ‘#’ in program
   27 |