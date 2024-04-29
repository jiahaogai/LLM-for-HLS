#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double sum;
  
<<<<<<< HEAD
=======
#pragma scop
  
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
<<<<<<< HEAD
=======
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{4}
      for (k = 0; k < 60; k++) {
        sum += alpha * A[i][k] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
<<<<<<< HEAD
=======
  
#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}