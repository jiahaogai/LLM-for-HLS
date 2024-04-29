Code: ### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}
#pragma ACCEL PARALLEL FACTOR=auto{10}

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{2}
      for (k_col = 0; k_col < 80; k_col++) {
        mult = alpha * A[k][k_col];
        
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
        for (j = 0; j < 80; j++) {
          C[i][j] += mult * B[k][j];
        }
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:6: error: unknown type name ‘pragma’; did you mean ‘_Pragma’?
    1 | ### #pragma ACCEL kernel
      |      ^~~~~~
      |      _Pragma
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:19: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘kernel’
    1 | ### #pragma ACCEL kernel
      |                   ^~~~~~

Please check the code and try again.
Code: ### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}
#pragma ACCEL PARALLEL FACTOR=auto{10}

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}