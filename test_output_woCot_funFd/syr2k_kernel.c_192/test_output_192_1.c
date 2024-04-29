#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//#pragma scop
=======
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
<<<<<<< HEAD
      if (j <= i) {
        C[i][j] *= beta;
      }
=======
      C[i][j] *= beta;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        if (j <= i) {
          C[i][j] += A[j][k] * alpha * B[i][k] + B[j][k] * alpha * A[i][k];
        }
      }
    }
  }
//#pragma endscop
=======
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j] + alpha * B[i][k] * A[k][j];
      }
    }
  }
  
#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}