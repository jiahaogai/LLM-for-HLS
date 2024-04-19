- `#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `v1` with an automatically determined factor of 1.
- `#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `v2` with an automatically determined factor of 1.
- `#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `u1` with an automatically determined factor of 1.
- `#pragma ACCEL PARALLEL reduction=u2 FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `u2` with an automatically determined factor of 1.
- `#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `y` with an automatically determined factor of 1.
- `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1}`: Concurrently execute loop iterations, performing a reduction operation using variable `z` with an automatically determined factor of 1.

#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{120}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp4 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp2 += A[i][j] * u2[j];
      tmp3 += A[i][j] * v2[j];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{2}
    x[i] = x[i] + alpha * ((u1[0] * tmp1) + (u2[0] * tmp2) + (v1[0] * tmp4) + (v2[0] * tmp3));
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    double tmp5 = 0.0;
    double tmp6 = 0.0;
    double tmp7 = 0.0;
    double tmp8 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp5 FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      tmp5 += A[j][i] * u1[j];
      tmp7 += A[j][i] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp6 FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      tmp6 += A[j][i] * u2[j];
      tmp8 += A[j][i] * v2[j];
    }
    
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{1}
    w[i] = beta * w[i] + alpha * ((v1[0] * tmp5) + (v2[0] * tmp6) + (tmp7) + (tmp8));
  }
}