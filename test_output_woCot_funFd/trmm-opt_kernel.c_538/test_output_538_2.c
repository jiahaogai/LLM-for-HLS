#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form B := alpha*A*B,
=======
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
    }
    
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
=======
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; ++k) {
        sum += alpha * A[i][k] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}