#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      temp = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        mult = alpha * A[i][k] * B[k][j];
        temp += mult;
      }
      C[i][j] = temp;
    }
  }
}