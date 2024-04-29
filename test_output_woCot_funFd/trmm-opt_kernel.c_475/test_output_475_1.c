#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{10}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}