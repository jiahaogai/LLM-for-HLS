#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_syr2k(int n,double alpha,double beta,double C[80][80],double A[80][70],double B[70][80])
=======
void kernel_syr2k(int n,double alpha,double beta,double C[90][90],double A[90][90],double B[90][90])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
<<<<<<< HEAD
// => Form C := alpha*C + beta*A*B**T
=======
// => Form C := alpha*A*B**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
=======
  for (i = 0; i < 90; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 0; j < 90; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 70; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 90; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 90; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}