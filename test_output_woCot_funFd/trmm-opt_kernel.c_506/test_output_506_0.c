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
// => A is NIxNK
//B is NIxNJ
// => B is modified
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
// => A is NKxNI
//B is NKxNJ
// => B is modified
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }

    for (k = 0; k < 60; k++) {
       for (j = 0; j < 80; j++) {
         B[i][j] += A[k][i] * B[k][j];
       }
     }
  }
}