Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{8}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{6}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
Error: 
Please check the code and try again.
Code: 
#include <math.h>
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{6}

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        for (int _in_j = 0; _in_j < 60; _in_j++) {
          temp2 += A[i][_in_j] * B[k][_in_j] * alpha;
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}