#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
<<<<<<< HEAD
      for (k = 0; k < 60; k++) {
=======
      for (k = 0; k < 60; ++k) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        sum += alpha * A[i][k] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
//#pragma endscop
}