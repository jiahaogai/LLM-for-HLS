#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(double alpha,double beta,double C[400][400],double A[400][300],double B[400][300])
=======
void kernel_syr2k(double alpha,double beta,double C[250][250],double A[250][250],double B[250][250])
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
=======
// => Form C := alpha*A*B**T + beta*C,
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
=======
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 250; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 300; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 300; j++) {
=======
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 250; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 250; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}