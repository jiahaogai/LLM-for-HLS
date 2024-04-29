#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[400],double A[400],double B[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i * 80 + j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (int jj = 0; jj < 80; jj++) {
        C[i * 80 + jj] += alpha * A[i * 80 + j] * B[j * 80 + jj];
      }
    }
  }
}