7. For the inner loop, perform parallel reduction on variable "x" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1_2}`

8. For the inner loop, perform parallel reduction on variable "z" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1_3}`

#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = u1[i] * v2[0];
    A[i][0] = alpha * tmp + A[i][0];
    x[i] = alpha * tmp + x[i];
    y[0] = beta * y[0] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
    v1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp += A[i][j] * u2[j];
      v1[i] += A[i][j] * v2[j];
    }
    A[i][0] = tmp;
    y[0] = beta * y[0] + tmp;
    w[0] = alpha * u2[0] * v1[0] + beta * w[0];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
    z[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp += A[i][j] * x[j];
      z[i] += A[i][j] * y[j];
    }
    A[i][0] = tmp;
    w[0] = alpha * tmp + beta * w[0];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 40; i++) {
    double tmp = u1[i] * v2[0];
    x[i] = tmp + x[i];
    y[0] = y[0] + z[i];
  }
}