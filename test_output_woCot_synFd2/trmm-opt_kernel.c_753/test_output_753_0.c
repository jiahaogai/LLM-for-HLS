#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form B := alpha*A*B,
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
        B[i][j] *= alpha;
     }
  }
//TRANSA = 'N'
//TRANSB = 'N'
// => Form B := alpha*A*B,
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       double sum = 0.0;
       for (k = 0; k < 60; ++k) {
         sum += A[i][k] * B[k][j];
       }
       B[i][j] = sum;
     }
  }
}