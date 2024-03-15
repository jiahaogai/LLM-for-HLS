#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double uu = 0.0;
    double vv = 0.0;
    double ww = 0.0;
    double uv = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 120; j++) {
      tmp1 = A[i][j] * u1[j];
      tmp2 = A[i][j] * v1[j];
      uu += u1[j] * tmp1;
      vv += v1[j] * tmp2;
      uv += u1[j] * tmp2;
      ww += w[j] * A[i][j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 120; j++) {
      x[i] += v2[j] * tmp2;
      y[i] += u2[j] * tmp1;
      z[i] += (A[i][j] * ((u1[j] * v1[j]) + (w[j] * uv + uu * vv 
                                              + ww))) - x[i] - y[i];
    }
  }
}