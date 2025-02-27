#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=1
#pragma ACCEL PARALLEL FACTOR=10
void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=2
  
#pragma ACCEL PARALLEL FACTOR=32
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=4
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=1
    
#pragma ACCEL PARALLEL FACTOR=32
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=4
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k];
        C[i][j] += mult * B[k][j];
      }
    }
  }
}