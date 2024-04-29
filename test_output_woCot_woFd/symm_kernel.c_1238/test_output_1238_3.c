- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this inner loop to control initiation interval.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

- `#pragma ACCEL PARALLEL FACTOR=auto{60}`: Execute loop iterations concurrently, taking advantage of parallelism for the outer loop.

- `#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{32}`: Execute loop iterations concurrently, with a reduction operation on the variable `temp1`.

- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this inner loop to control initiation interval.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

- `#pragma ACCEL PARALLEL FACTOR=auto{80}`: Execute loop iterations sequentially, not concurrently, for the inner loop.


**#pragma ACCEL kernel**



#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1 = 0.0;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      temp2 += A[k][j] * B[k][j];
    }
    C[0][j] = temp2;
    temp2 = 0.0;
    
#pragma ACCEL PARALLEL reduction = temp1 FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      temp1 += A[k][j] * C[k][j];
    }
    C[0][j] = alpha * temp1 + beta * C[0][j];
    temp1 = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 1; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp1 FACTOR=auto{32}
      for (k = 0; k < 60; k++) {
        temp1 += A[i][k] * C[k][j];
      }
      C[i][j] = temp1;
    }
  }
}