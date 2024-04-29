Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        for (__local int __index_temp = 0; __index_temp < 60; ++__index_temp) {
          double A_elem = A[i][__index_temp];
          double B_elem = B[__index_temp][j];
          temp2 += A_elem * B_elem;
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:14: error: ‘__local’ undeclared (first use in this function)
   32 |         for (__local int __index_temp = 0; __index_temp < 60; ++__index_temp) {
      |              ^~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:14: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:21: error: expected ‘;’ before ‘int’
   32 |         for (__local int __index_temp = 0; __index_temp < 60; ++__index_temp) {
      |                     ^~~~
      |                     ;
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:44: error: ‘__index_temp’ undeclared (first use in this function)
   32 |         for (__local int __index_temp = 0; __index_temp < 60; ++__index_temp) {
      |                                            ^~~~~~~~~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PI