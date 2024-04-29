Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{4}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mul = alpha * A[i][k] * B[k][k_col];
        temp_x += mul;
      }
      C[i][k_col] = temp_x;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:38: error: ‘j_col’ undeclared (first use in this function); did you mean ‘k_col’?
   35 |         mul = alpha * A[i][k] * B[k][j_col];
      |                                      ^~~~~
      |                                      k_col
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:38: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{4}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mul = alpha * A[i][k] * B[k][k_col];
        temp_x += mul;
      }
      C[i][k_col] = temp_x;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:38: error: ‘j_col’ undeclared (first use in this function); did you mean ‘k_col’