#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
<<<<<<< HEAD
  int trana = 3;
//B is TRANSB = 'N'
  int tranb = 1;
  
#pragma scop
=======
  int m = 60;
  int n = 60;
  int k1 = 80;
  int k2 = 60;
  double alpha1 = alpha;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
<<<<<<< HEAD
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{80}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += alpha * A[k][i] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
  
#pragma endscop
=======
      B[i][j] *= alpha1;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[k][i] * B[k][j];
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}