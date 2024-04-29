Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
        for (auto l = 0; l < 60; l++) {
          temp1[l] = A[i][l] * B[l][j];
        }
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
        for (auto l = 0; l < 60; l++) {
          temp2 += temp1[l] * A[k][l];
        }
        C[k][j] += temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:19: warning: type defaults to ‘int’ in declaration of ‘l’ [-Wimplicit-int]
   34 |         for (auto l = 0; l < 60; l++) {
      |                   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:11: error: ‘temp1’ undeclared (first use in this function); did you mean ‘temp2’?
   35 |           temp1[l] = A[i][l] * B[l][j];
      |           ^~~~~
      |           temp2
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:11: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:38:19: warning: type defaults to ‘int’ in declaration of ‘l’ [-Wimplicit-int]
   38 |         for (auto l = 0; l < 60; l++) {
      |                   ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0;