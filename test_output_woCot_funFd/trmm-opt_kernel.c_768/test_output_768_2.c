#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form B := alpha*A*B,
//A is NIxNK
//B is NKxNJ
// => B is updated
  for (i = 0; i < 60; i++) {
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}