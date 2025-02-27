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
//B is TRANSB = 'N'
// => B is N-by-M
// => therefore: M = 80
// =>               N = 60
// =>               K = 60
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 60; k++) {
     for (j = 0; j < 80; j++) {
       double sum = (double )0;
       for (j = 0; j < 80; j++) {
         sum += A[k][j] * B[j][i];
       }
       B[k][i] = sum;
     }
  }
}