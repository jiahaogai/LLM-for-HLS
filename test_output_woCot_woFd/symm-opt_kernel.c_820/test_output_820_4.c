#pragma ACCEL kernel

__kernel
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
  spy_kernel_symm_0:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    spy_kernel_symm_1:
    for (j = 0; j < 80; j++) {
      temp_1 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp_1 FACTOR=auto{4}
      spy_kernel_symm_2:
      for (k_col = 0; k_col < 60; k_col++) {
        mult = alpha * A[i][k_col] * B[k_col][j];
        temp_1 += mult;
      }
      C[i][j] = temp_1;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spy_kernel_symm_3:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    spy_kernel_symm_4:
    for (j = 0; j < 80; j++) {
      temp_2 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp_2 FACTOR=auto{__PARA__L3}
      spy_kernel_symm_5:
      for (k = 0; k < 60; k++) {
        mult = beta * C[k][j];
        temp_2 += mult;
      }
      C[i][j] = temp_2;
    }
  }
}