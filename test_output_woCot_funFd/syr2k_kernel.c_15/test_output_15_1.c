Code: #pragma ACCEL PIPELINE auto{off}` - Do not pipeline the loop iterations.
  - `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the loop whole, without dividing it into smaller parts.
  - `#pragma ACCEL PARALLEL FACTOR=auto{2}` - Execute loop iterations concurrently in parallel with a factor of 2 to maximize hardware resource utilization.

#pragma ACCEL kernel
 
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
int i;
int j;
int k;
double sum;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 80; i++) {
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
    for (k = 0; k < 60; ++k) {
      sum += A[i][k] * B[k][j];
    }
    C[i][j] *= beta;
    C[i][j] += alpha * sum;
  }
}
//#pragma endscop
}