#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    for (j = 0; j < 120; j++) {
      A[i][j] += + u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    double tmp_A = 0.0;
    int P = 1 + (((int )70) / i);
    for (j = 1; j <= P * 70; j++) {
      if (j < 1 + (i * 70)) {
        tmp_x += x[j] + w[j] * v1[i] ;
        tmp_y += y[j] + w[j] * v2[i] ;
        tmp_z += z[j] + w[j] * A[i][j] ;
      }
    }
    x[i] = tmp_x;
    y[i] = tmp_y;
    z[i] = tmp_z;
    for (j = 1; j <= P * 70; j++) {
      if (j < 1 + (i * 70)) {
        A[i][j] = A[i][j] + alpha * (x[i] * v1[j] + y[i] * v2[j]);
      }
    }
    z[i] = z[i] + 0.0 + beta * tmp_A;
  }
}