Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{32}
        for (long long n = 0LL; n < 60LL; n++) {
          temp1[n] = A[i][n] * B[n][j];
        }
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
        for (long long n = 0LL; n < 60LL; n++) {
          temp2 += temp1[n] * A[k][n];
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Parameters:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Parameters:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Parameters:
      |               ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:13:1: error: stray ‘##’ in program
   13 | ### Types:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:13:3: error: stray ‘#’ in program
   13 | ### Types:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:17:1: error: stray ‘##’ in program
   17 | ### Constants:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:17:3: error: stray ‘#’ in program
   17 | ### Constants:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:211:1: error: stray ‘##’ in program
  211 | ## #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:211:4: error: stray ‘#’ in program
  211 | ## #pragma ACCEL kernel
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:211