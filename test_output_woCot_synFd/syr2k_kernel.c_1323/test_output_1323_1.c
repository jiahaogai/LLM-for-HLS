Code: #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double tmp;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 0; i < 80; i++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = 0; k < 60; k++) {
        tmp += A[i][k] * B[j][k];
      }
      C[i][j] = alpha * tmp + beta * C[i][j];
    }
  }
  
#pragma endscop
}