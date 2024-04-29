Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      C[j][j] += alpha * A[j][k] * A[j][k];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = i + 1; j < 80; j++) {
      C[i][j] *= beta;
      C[j][i] *= beta;
      C[i][j] += alpha * A[i][k] * A[j][k];
      C[j][i] += alpha * A[j][k] * A[i][k];
    }
    C[i][i] *= beta;
    C[i][i] += alpha * A[i][k] * A[i][k];
  }
//#pragma endscop
}
#pragma ACCEL kernel
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      C[j][j] += alpha * A[j][k] * B[j][k];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = i + 1; j < 80; j++) {
      C[i][j] *= beta;
      C[j][i] *= beta;
      C[i][j] += alpha * A[i][k] * B[j][k];
      C[j][i] += alpha * A[j][k] * B[i][k];
    }
    C[i][i] *= beta;
    C[i][i] += alpha * A[i][k] * B[i][k];
  }
//#pragma endscop