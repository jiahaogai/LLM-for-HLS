#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{4}
      for (k = 0; k < 60; k++) {
        mult = alpha * A[i][k];
        sum += mult * B[k][j];
      }
      B[i][j] = sum;
    }
  }
}