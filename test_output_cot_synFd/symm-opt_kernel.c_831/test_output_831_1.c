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
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
        for (__PARA__L1 = 0; __PARA__L1 < 60; __PARA__L1++) {
          double temp1 = A[i][__PARA__L1] * B[__PARA__L1][j];
          temp2 += temp1;
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: error: ‘__PARA__L1’ undeclared (first use in this function)
   34 |         for (__PARA__L1 = 0; __PARA__L1 < 60; __PARA__L1++) {
      |              ^~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:34:14: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:11: error: ‘temp1’ undeclared (first use in this function); did you mean ‘temp2’?
   35 |           temp1 = A[i][__PARA__L1] * B[__PARA__L1][j];
      |           ^~~~~
      |           temp2
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:34: error: ‘__PARA__L1’ undeclared (first use in this function); did you mean ‘k’?
   35 |           temp1 = A[i][__PARA__L1] * B[__PARA__L1][j];
      |                                      ^~~~~~~~~~
      |                                      k
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:50: error: ‘j’ undeclared (first use in this function)
   35 |           temp1 = A[i][__PARA__L1] * B[__PARA__L1][j];
      |                                                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:36:25: error: ‘temp2’ undeclared (first use in this function); did you mean ‘temp1’?
   36 |           C[i][j] += temp2;
      |                         ^~~~~
      |                         temp1