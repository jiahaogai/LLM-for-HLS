<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
Code: 
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is M(=80) by K(=60)
//B is M(=80) by K(=60)
//C is M(=80) by M(=80)
=======
  double tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
=======
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{2}
      for (k = 0; k < 60; ++k) {
        tmp += A[i][k] * B[k][j];
      }
      C[i][j] += tmp * alpha;
    }
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * C[j][i];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
  
#pragma endscop
}