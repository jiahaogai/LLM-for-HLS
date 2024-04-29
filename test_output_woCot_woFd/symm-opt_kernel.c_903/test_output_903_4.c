- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}`: Perform reduction operation for variable `C` with an appropriate factor.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      double temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}
      for (k_col = 0; k_col < 80; k_col++) {
        mult = alpha * A[k][k_col];
        temp2 += mult * B[k_col][j];
      }
      C[i][j] += temp2;
    }
  }
}