#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NIxNK
//C is NIxNI
  
#pragma scop
=======
void kernel_syr2k(double alpha,double beta,double C[400],double A[400],double B[400])
{
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{70}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
=======
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      C[i * 80 + j] *= beta;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
=======
    for (j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (int jj = 0; jj < 80; jj++) {
        C[i * 80 + jj] += alpha * A[i * 80 + j] * B[j * 80 + jj];
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}