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
//B is NIxNK
//C is NKxNK
  
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
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:7: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    4 | **Text:**
      |       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:7: error: stray ‘`’ in program
    4 | **Text:**
      |       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: error: stray ‘`’ in program
    5 | #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: error: stray ‘`’ in program
    5 | #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:1: error: stray ‘`’ in program
    6 | 
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: stray ‘`’ in program
    7 | #pragma ACCEL PIPELINE auto{}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:1: error: stray ‘`’ in program
    7 | #pragma ACCEL PIPELINE auto{}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:1: error: stray ‘`’ in program
    8 | #pragma ACCEL TILE FACTOR=auto{1}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:1: error: stray ‘`’ in program
    8 | #pragma ACCEL TILE FACTOR=auto{1}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:9:1: error: stray ‘`’ in program
    9 | #pragma ACCEL PARALLEL FACTOR=auto{16}
      | ^
/root/autodl-tmp/