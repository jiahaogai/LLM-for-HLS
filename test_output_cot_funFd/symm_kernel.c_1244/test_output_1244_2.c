Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{60}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{80}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{flatten}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{60}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{60}
Error: 
Please check the code and try again.
Code: #pragma ACCEL BLOCK FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: 
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}