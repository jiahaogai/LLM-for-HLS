#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  double temp_y;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{10}
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        temp_x = A[i * 60 + k] * B[k_col];
        temp2 = alpha * temp_x;
        C[i * 60 + k] += temp2;
      }
      temp_y = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_y FACTOR=auto{4}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 80; k++) {
        mul = beta * C[i * 60 + k];
        temp_y += mul;
        C[i * 60 + k] = temp_y;
        temp_y -= mul;
      }
    }
  }
}