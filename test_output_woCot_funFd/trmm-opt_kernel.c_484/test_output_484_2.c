<<<<<<< HEAD
- `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{80}`: Perform reduction operation on variable 'B' with a parallel factor of 80.
  
#pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
int i;
int j;
int k;
double sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
  for (j = 0; j < 60; j++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{6}
    for (k = 0; k < 80; ++k) {
      sum += A[i][k] * B[k][j];
    }
    A[i][j] = sum;
  }
}
//#pragma endscop
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
