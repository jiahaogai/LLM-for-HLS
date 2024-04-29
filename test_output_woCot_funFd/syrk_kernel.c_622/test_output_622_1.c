#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNI
//K is NK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
  
#pragma endscop
}