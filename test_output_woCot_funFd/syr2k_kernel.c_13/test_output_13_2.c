#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
<<<<<<< HEAD
//TRANSB = 'N'
=======
//TRANSB = 'T'
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
// => Form C := alpha*A*B' + alpha*B*A' + beta*C,
//A is NIxNK
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{5}
    for (k = 0; k < 60; k++) {
      C[j][k] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (i = 0; i < 80; i++) {
        C[j][k] += alpha * A[i][k] * B[i][j];
      }
    }
  }
  
#pragma endscop
}