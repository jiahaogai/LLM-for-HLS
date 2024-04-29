<<<<<<< HEAD
- `#pragma ACCEL TILE FACTOR=auto{2}`: Tile the inner loop into 2 smaller tiles that are executed sequentially.
=======
Code: #pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{16}
#pragma ACCEL PARALLEL FACTOR=auto{8}
void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
//#pragma endscop
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
