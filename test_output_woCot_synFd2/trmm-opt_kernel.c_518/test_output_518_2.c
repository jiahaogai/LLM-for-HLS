#pragma ACCEL kernel

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
//B is N-by-N
// => B is overwritten with alpha*A**T*B
// => DIMB = N
//B is TRANSB = 'N'
// => B is N-by-M
//A is TRANSA = 'T'
// => A is N-by-N
//B is TRANSB = 'N'
// => B is M-by-N
// => DIMB = M
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; ++k) {
        sum += alpha * A[i][k] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
  
#pragma endscop
}