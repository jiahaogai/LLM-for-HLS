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
        double temp1 = alpha * A[i][k];
        __loop__L1:
        for (__seq_len__L1 = 0; __seq_len__L1 < 60; __seq_len__L1++) {
          temp2 += B[k][__seq_off__L1 + __loop__L1] * temp1;
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: error: ‘__seq_len__L1’ undeclared (first use in this function)
   34 |         for (__seq_len__L1 = 0; __seq_len__L1 < 60; __seq_len__L1++) {
      |              ^~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:25: error: ‘__seq_off__L1’ undeclared (first use in this function)
   35 |           temp2 += B[k][__seq_off__L1 + __loop__L1] * temp1;
      |                         ^~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:41: error: ‘__loop__L1’ undeclared (first use in this function)
   35 |           temp2 += B[k][__seq_off__L1 + __loop__L1] * temp1;
      |                                         ^~~~~~~~~~

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
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }