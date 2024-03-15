 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double uu = 0.0;
    double vv = 0.0;
    double ww = 0.0;
    double xx = 0.0;
    double yy = 0.0;
    double zz = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 120; j++) {
      tmp1 = A[i][j] * u1[j];
      tmp2 = A[i][j] * v1[j];
      uu += A[i][j] * u1[j] * v1[j];
      vv += A[i][j] * u1[j] * v1[j];
      ww += A[i][j] * v1[j] * v1[j];
      xx += A[i][j] * x[j];
      yy += A[i][j] * y[j];
      zz += A[i][j] * z[j];
    }
    x[i] = tmp1 - xx;
    y[i] = tmp2 - yy;
    z[i] = A[i][i] * zz - z[i];
    double delta = (y[i] - vv - x[i] * uu) / n;
    w[i] = z[i] + alpha * ((x[i]) * delta - y[i]);
  }
}
