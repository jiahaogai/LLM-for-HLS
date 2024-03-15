#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    z[i] = 0.0;
    y[i] = 0.0;
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double Ai;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 120; j++) {
      Ai = A[i][j];
      z[i] = Ai * v1[j] + z[i];
      y[i] = u1[j] * Ai + y[i];
      tmp += Ai * u2[j];
      tmp_x += Ai * v2[j] * x[j];
      tmp_y += Ai * v2[j] * y[j];
    }
    x[i] = beta * x[i] + alpha * u1[i] * y[i] + z[i];
    y[i] = beta * y[i] + alpha * tmp;
    double tmp_x_ = x[i];
    double tmp_y_ = y[i];
    double A_i = A[i][i];
    x[i] = A_i * tmp_x_ + (1.0 + alpha) * x[i];
    y[i] = A_i * tmp_y_ + (1.0 + alpha) * y[i];
  }
}