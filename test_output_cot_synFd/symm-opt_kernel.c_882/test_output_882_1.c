Code: ### #pragma ACCEL kernel

c
 
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
        for (jj = 0; jj < 60; jj++) {
          temp1 = A[i][jj] * B[jj][j];
          temp2 += temp1;
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
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
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:19: error: unknown type name ‘kernel’

Please check the code and try again.
Code: ### #pragma ACCEL kernel

c
 
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j]