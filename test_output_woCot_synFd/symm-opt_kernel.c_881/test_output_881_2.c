#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spy_kernel_symm_0:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    spy_kernel_symm_1:
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    spy_kernel_symm_2:
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      spy_kernel_symm_3:
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        spy_kernel_symm_4:
        for (long range_l3 = 0; range_l3 < 60L; range_l3++) {
          temp2 += A[i][range_l3] * B[range_l3][j];
        }
        mult = alpha * temp2;
        C[i][j] += mult;
      }
    }
  }
}