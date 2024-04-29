#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mul = alpha * A[i][k] * B[k][j_col];
        temp_x += mul;
      }
      C[i][j_col] = temp_x + beta * C[i][j_col];
    }
  }
}