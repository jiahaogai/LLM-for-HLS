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
        k_col = 0;
        temp_y = A[i][k];
        mul = temp_y * B[k][j];
        while (k_col < 60) {
          
#pragma ACCEL PIPELINE auto{flatten}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{4}
          C[i][j] += mul * A[k][k_col];
          k_col++;
        }
      }
      C[i][j] *= alpha;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
  }
}