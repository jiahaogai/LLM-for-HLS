#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{8}

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
// => A is N-by-N
//B is TRANSB = 'N'
// => B is N-by-M
// => therefore: M = 80
// =>               K = 60
// =>               N = 60
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{2}
    for (j = 0; j < 60; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
      for (k = 0; k < 60; ++k) {
        sum += A[i][k] * B[k][j];
      }
      A[i][j] = alpha * sum;
    }
  }
}