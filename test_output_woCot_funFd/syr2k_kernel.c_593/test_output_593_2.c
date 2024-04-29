#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
<<<<<<< HEAD
// => Form C := alpha*A*B**T + beta*C,
=======
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//A is ROW MAJOR
//B is ROW MAJOR
//C is ROW MAJOR
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
=======
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}