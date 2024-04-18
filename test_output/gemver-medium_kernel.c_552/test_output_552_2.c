#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    double Ai;
    double u1_i;
    double v1_i;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      u1_i = u1[i] * v1[j];
      tmp += Ai * u1_i;
      Ai = A[j][i];
      v1_i = v1[i] * u1[j];
      tmp_x += Ai * v1_i;
      Ai = A[i][j];
      u2_i = u2[i] * v2[j];
      tmp_y += Ai * u2_i;
      Ai = A[j][i];
      v2_i = v2[i] * u2[j];
      tmp_z += Ai * v2_i;
    }
    z[i] = beta * z[i] + tmp;
    y[i] = beta * y[i] + tmp_x;
    x[i] = alpha * x[i] + tmp_y;
    w[i] = alpha * w[i] + tmp_z;
  }
}