#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double tmp;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        tmp += A[i][k] * B[k][j];
      }
      temp2 = tmp * alpha;
      C[i][j] += temp2;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * C[i][j];
    }
  }
}