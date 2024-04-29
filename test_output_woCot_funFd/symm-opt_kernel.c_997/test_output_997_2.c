Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double tmp;
  double mul;
  double tmp_x;
  double tmp_y;
  double tmp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      tmp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        tmp_x = A[i * 60 + k];
        tmp_y = B[k * 80 + j];
        mul = tmp_x * tmp_y;
        tmp2 += mul;
      }
      C[i * 80 + j] = alpha * tmp2 + beta * C[i * 80 + j];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:38:14: error: ‘jj’ undeclared (first use in this function); did you mean ‘j’?
   38 |         for (jj = 0; jj < 60; jj++) {
      |              ^~
      |              j
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:38:14: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double tmp;
  double mul;
  double tmp_x;
  double tmp_y;
  double tmp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      tmp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        tmp_x = A[i * 60 + k];
        tmp_y = B[k * 80 + j];
        mul = tmp_x * tmp_y;
        tmp2 += mul;
      }
      C[i * 80 + j] = alpha * tmp2 + beta * C[i * 80 + j];