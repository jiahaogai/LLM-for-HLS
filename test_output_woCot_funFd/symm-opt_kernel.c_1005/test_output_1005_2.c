Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 80; j++) {
      temp_sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_sum FACTOR=auto{4}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mult = alpha * A[i][k] * B[k][j_col];
        temp_sum += mult;
      }
      if (beta == 0.0) {
        C[i][j] = temp_sum;
      }
      else {
        C[i][j] = beta * C[i][j] + temp_sum;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:7: error: ‘temp_sum’ undeclared (first use in this function)
   26 |       temp_sum = 0.0;
      |       ^~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:26:7: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:39: error: ‘j_col’ undeclared (first use in this function); did you mean ‘k_col’?
   32 |         mult = alpha * A[i][k] * B[k][j_col];
      |                                       ^~~~~
      |                                       k_col

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 80; j++) {
      temp_sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_sum FACTOR=auto{4}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mult = alpha * A[i][k] * B[k][j_col];
        temp_sum += mult;
      }
      if (beta == 0.0) {
        C[