#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spy_kernel_symm:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    spy_kernel_symm_k_col:
    for (k_col = 0; k_col < 80; k_col += 4) {
      double temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{1}
      spy_kernel_symm_k:
      for (k = 0; k < 60; k++) {
        mult = alpha * A[i][k] * B[k][k_col];
        temp_x += mult;
      }
      C[i][k_col] = temp_x;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    spy_kernel_symm_j:
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * C[i][j];
    }
  }
}