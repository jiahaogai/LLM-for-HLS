#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[400][400],double A[400][300],double B[300][400])
=======
void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
<<<<<<< HEAD
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NORMAL
//B is NORMAL
//C is SYMMETRIC
=======
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 400; j++) {
      C[i][j] *= beta;
=======
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      C[i * 64 + j] *= beta;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 300; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 400; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 64; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 64; j++) {
        C[i * 64 + j] += alpha * A[i * 64 + k] * B[k * 64 + j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}