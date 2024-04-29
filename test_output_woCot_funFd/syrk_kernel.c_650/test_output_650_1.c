Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  double tmp;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (k = 0; k < 60; ++k) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      for (i = 0; i < 80; ++i) {
        tmp += A[i][k] * A[i][j];
      }
      C[j][k] *= beta;
      C[j][k] += alpha * tmp;
    }
  }
  
#pragma endscop
}