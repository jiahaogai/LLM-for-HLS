- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `v1` with a factor of 1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `u1` with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=y FACTOR=auto{8}`: Execute loop iterations concurrently and apply reduction operation on variable `y` with a factor of 8.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `v2` with a factor of 1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=u2 FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `u2` with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{8}`: Execute loop iterations concurrently and apply reduction operation on variable `z` with a factor of 8.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL reduction=a FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `a` with a factor of 1.
- `#pragma ACCEL PARALLEL reduction=b FACTOR=auto{1}`: Execute loop iterations concurrently and apply reduction operation on variable `b` with a factor of 1.


#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[j][i] * y[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 400; i++) {
    x[i] = x[i] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      w[i] += alpha * A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{__PARA__L8}
    for (j = 0; j < 400; j++) {
      u1[i] += alpha * y[j] * A[j][i];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{__PARA__L10}
    for (j = 0; j < 400; j++) {
      v1[i] += alpha * x[j] * A[j][i];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=u2 FACTOR=auto{__PARA__L12}
    for (j = 0; j < 400; j++) {
      u2[i] += beta * v2[j] * w[j] + u1[i];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L13}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{__PARA__L14}
    for (j = 0; j < 400; j++) {
      v2[i] += beta * y[j] * w[j] + v1[i];
    }
  }
}