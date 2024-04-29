4. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
5. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
6. `#pragma ACCEL PARALLEL FACTOR=auto{5}`: Execute loop iterations in parallel, with a factor of 5.
7. `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations in parallel, with a factor of 4.

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      if (j <= i) {
        C[i][j] *= beta;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{5}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        if (j <= i) {
          C[i][j] += A[j][k] * alpha * B[i][k] + B[j][k] * alpha * A[i][k];
        }
      }
    }
  }
//#pragma endscop
}