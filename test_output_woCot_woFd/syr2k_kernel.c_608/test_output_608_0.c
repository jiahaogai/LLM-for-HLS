5. `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{10}`: The loop over variable `i` is parallelized, and shared variables are updated every 10 iterations.

6. `#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}`: The loop over variable `k` is parallelized, and shared variables are updated every iteration.

7. `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}`: The loop over variable `k` is parallelized, and shared variables are updated every iteration.

8. `#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}`: The loop over variable `j` is parallelized, and shared variables are updated every iteration.

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        A[i][j] += alpha * B[k][j] * A[j][k];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        B[i][j] += alpha * A[j][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}