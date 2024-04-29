- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{60}`: Execute loop iterations concurrently with a reduction variable 'C' and a parallel factor of 60.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{15}
      for (k = 0; k < 60; ++k) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{15}
      for (k = 0; k < 80; ++k) {
        temp2 += C[i][k] * A[k][j];
      }
      C[i][j] = temp2 + alpha * temp1 + beta * C[i][j];
    }
  }
}