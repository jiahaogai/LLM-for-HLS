- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Execute loop iterations concurrently with a factor of 16.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.

### Template:
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
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{80}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}