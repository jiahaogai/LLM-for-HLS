Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double tmp;
  double mul;
  double temp_x;
  double temp_y;
  double temp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        tmp = A[i * 60 + k] * B[k * 80 + j];
        mul = alpha * tmp;
        temp_x = C[i * 80 + k_col];
        temp_y = mul + beta * temp_x;
        temp2 = temp2 + temp_y;
      }
      C[i * 80 + j] = temp2;
    }
  }
}