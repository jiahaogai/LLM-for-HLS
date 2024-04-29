#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{60}
=======
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{5}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{6}
      for (j = 0; j < 60; j++) {
        B[i][k] += A[i][j] * B[j][k];
=======
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{6}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[i][k] * B[k][j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}