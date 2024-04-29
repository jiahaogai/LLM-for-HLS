Code: #pragma ACCEL kernel

void kernel_spmv(double M[240][240],double vout[240],double vin[240],double zero,double one)
{
  int i;
  int j;
  double sum;
  double PI = 3.14159265358979323846;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 240; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 240; j++) {
      sum += M[i][j] * vin[j];
    }
    vout[i] = (sum + zero);
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_syrk(double A[240][240],double C[240][240],double zero,double one)
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  syrk_1:
  for (i = 0; i < 240; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    syrk_2:
    for (j = 0; j < 240; j++) {
      C[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      syrk_3:
      for (k = 0; k < 240; k++) {
        mult = A[i][k] * A[k][j];
        C[i][j] += mult;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60],double zero,double one)
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  syr2k_1:
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    syr2k_2:
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    syr2k_3:
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      syr2k_4:
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k] * B[k][j];
        C[i][j] += mult;
      }
    }
  }
}