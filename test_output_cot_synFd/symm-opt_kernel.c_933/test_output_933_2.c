#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double temp1 = 0.0;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp1 FACTOR=auto{10}
      for (k = 0; k < 60; ++k) {
        temp1 += A[i][k] * B[j][k];
      }
      C[i][j] = temp1;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        temp2 += A[k][i] * B[k][j];
      }
      C[j][i] = alpha * temp2 + beta * C[j][i];
    }
  }
}