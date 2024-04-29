#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double tmp;
  double mul;
  double sum = 0.0;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{16}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mul = A[i][k] * B[k][k_col];
        tmp += mul;
      }
      sum = tmp + C[i][j];
      temp2 = alpha * sum + beta * C[i][j];
      C[i][j] = temp2;
    }
  }
}