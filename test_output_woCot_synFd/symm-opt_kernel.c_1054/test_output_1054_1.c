#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1 = 0.0;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{80}
      for (k = 0; k < 60; k++) {
        temp1 = alpha * A[i][k] * B[k][j];
        temp2 += temp1;
      }
      C[i][j] = beta * C[i][j] + temp2;
    }
  }
}