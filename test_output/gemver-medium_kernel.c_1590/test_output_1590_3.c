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
    double Ai;
    double u1_i;
    double v1_i;
    double u2_j;
    double v2_j;
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      u1_i = u1[i] * v1[j];
      v1_i = v1[i] * Ai;
      tmp = tmp + Ai * v1[j];
      u2_j = u2[j] * v2[i];
      v2_j = v2[j] * Ai;
      tmp_x = tmp_x + Ai * u2[j];
      tmp_y = tmp_y + v1_i + u1_i;
      tmp_z = tmp_z + v2_j + u2_j;
    }
    z[i] = beta * z[i] + alpha * tmp;
    y[i] = beta * y[i] + alpha * tmp_y;
    x[i] = beta * x[i] + alpha * tmp_x;
    w[i] = beta * w[i] + alpha * tmp_z;
  }
}