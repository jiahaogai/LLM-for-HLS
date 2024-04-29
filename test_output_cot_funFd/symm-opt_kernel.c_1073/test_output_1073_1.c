#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  spy_kernel_symm:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    spy_kernel_symm_middle:
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{__PARA__L1}
      spy_kernel_symm_inner:
      for (k = 0; k < 60; k++) {
        k_col = i * 60 + k;
        mul = alpha * A[k][j] * B[k][j];
        temp_x += mul;
      }
      C[i][j] = temp_x + beta * C[i][j];
    }
  }
}