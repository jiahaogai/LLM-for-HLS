#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{2}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
      tmp_x += A[i][j] * v1[j];
    }

    z[i] = beta * z[i] + tmp;
    y[i] = beta * y[i] + tmp_x;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 400; j++) {
      x[j] = beta * x[j] + y[i] * v2[j] + z[i] * w[j];
      tmp_y += A[j][i] * u1[j];
      tmp_z += A[j][i] * v1[j];
    }

    x[i] = alpha * x[i] + tmp_y;
    y[i] = alpha * y[i] + tmp_z;
  }
}