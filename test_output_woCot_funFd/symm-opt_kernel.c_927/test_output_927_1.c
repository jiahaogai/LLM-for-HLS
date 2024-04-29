Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction = C FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction = temp_x FACTOR=auto{__PARA__L1}
      double temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction = mul FACTOR=auto{__PARA__L2}
      double mul = 0.0;
      
#pragma ACCEL PIPELINE auto{__PARA__L3}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k_col = 0; k_col < 80; k_col++) {
        mul = A[k][k_col] * B[k_col][j];
        temp_x += mul;
      }
      temp_x = alpha * temp_x;
      C[i][j] += temp_x;
    }
  }
}