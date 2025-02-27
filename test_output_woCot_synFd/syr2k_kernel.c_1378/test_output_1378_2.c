**Optimization Parameters:**  
use_clock_enable = false  
use_stall_register = false  

**Memory Declarations:**  
double C[80][80]  
double A[80][60]  
double B[80][60]  

**Variables Declarations:**  
int i;  
int j;  
int k;  
double mult;  

**//#pragma scop//C := alpha*A*B' + alpha*B*A' + beta*C//#pragma endscop//**
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k] * B[k][j];
        C[i][j] += mult;
      }
    }
  }
}