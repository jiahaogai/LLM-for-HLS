#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double tmp;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        mult = alpha * A[i][k] * B[k][j];
        tmp += mult;
      }
      C[i][j] = beta * C[i][j] + tmp;
    }
  }
}