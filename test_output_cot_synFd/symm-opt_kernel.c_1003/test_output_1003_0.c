#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{10}
      for (k = 0; k < 60; k++) {
        mul = A[i][k] * B[k][j];
        temp1 += mul;
      }
      temp2 = C[i][j] * beta;
      temp1 = temp1 + temp2;
      C[i][j] = temp1;
    }
  }
}