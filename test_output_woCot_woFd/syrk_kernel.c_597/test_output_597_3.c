- `#pragma ACCEL TILE FACTOR=auto{8}`: Tile the loop, using a factor of 8.
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute loop iterations in parallel, using a factor of 2.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations in parallel, using a factor of 4.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute loop iterations in parallel, using a factor of 8.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations in parallel, using a factor of 4.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Execute loop iterations in parallel, using a factor of 8.

#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNI
//K is NK
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}