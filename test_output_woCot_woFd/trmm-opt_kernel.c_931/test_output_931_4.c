5. `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{8}`: Perform a parallel reduction operation on the variable `B` with a factor of 8 to improve parallelism and reduce computation time.
6. `#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}`: Perform a parallel reduction operation on the variable `A` with a factor of 1 to improve parallelism and reduce computation time.
7. `#pragma ACCEL PARALLEL reduction=alpha FACTOR=auto{1}`: Perform a parallel reduction operation on the variable `alpha` with a factor of 1 to improve parallelism and reduce computation time.

#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A => (60x60)
//B => (60x80)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{15}
    for (sum = 0.0, k = 0; k < 60; k++) {
      sum += alpha * A[i][k] * B[k][j];
    }
    B[i][j] = sum;
  }
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A => (60x60)
//B => (80x60)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{8}
    for (i = 0; i < 60; i++) {
      B[i][j] *= alpha;
    }
  }
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A => (60x60)
//B => (60x80)
//C => (60x80)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += A[i][k] * B[k][j];
      }
      A[i][j] = alpha * sum;
    }
  }
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*B**T + beta*C,
//A => (60x60)
//B => (80x60)
//C => (60x80)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += A[i][k] * B[j][k];
      }
      if (beta == 0.0) {
        C[i][j] = alpha * sum;
      }
      else {
        C[i][j] = alpha * sum + beta * C[i][j];
      }
    }
  }
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*B**T + beta*C,
//A => (60x60)
//B => (60x80)
//C => (80x60)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 60; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += A[k][j] * B[i][k];
      }
      if (beta == 0.0) {
        C[i][j] = alpha * sum;
      }
      else {
        C[i][j] = alpha * sum + beta * C[i][j];
      }
    }
  }
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form C := alpha*A**T*B + beta*C,
//A => (60x60)
//B => (80x60)
//C => (60x80)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += A[k][i] * B[j][k];
      }
      if (beta == 0.0) {
        C[i][j] = alpha * sum;
      }
      else {
        C[i][j] = alpha * sum + beta * C[i][j];
      }
    }
  }
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'T'
// => Form C := alpha*A**T*B**T + beta*C,
//A => (60x60)
//B => (80x60)
//C => (80x60)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 60; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction