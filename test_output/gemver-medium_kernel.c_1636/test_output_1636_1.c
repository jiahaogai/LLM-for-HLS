#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    double tmp5 = 0.0;
    double tmp6 = 0.0;
    double u_i;
    double v_i;
    double w_i;
    double x_i;
    double y_i;
    double z_i;
    double A_ii;
    double A_ip1_j;
    double A_i_j;
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      u_i = u1[i] * v1[j];
      v_i = v1[i] * v2[j];
      w_i = w[i] * v2[j];
      x_i = x[i] * v2[j];
      y_i = y[i] * u2[j];
      z_i = z[i] * u2[j];
      A_ii = A[i][i];
      A_ip1_j = A[i + 1][j];
      A_i_j = A[i][j];
      tmp1 += A_ii + A_ip1_j;
      tmp2 += A_i_j + u_i + v_i;
      tmp3 += A_i_j - x_i - y_i;
      tmp4 += A_ii + alpha * (u_i + v_i);
      tmp5 += A_ip1_j + alpha * (x_i - y_i);
      tmp6 += A_ii + beta * (z_i - w_i);
    }
    A[i][i] = tmp4;
    A[i + 1][i] = tmp5;
    A[i][i + 1] = tmp6;
    A[i][j] = tmp3;
    y[i] = tmp1;
    x[i] = tmp2;
  }
  double sum = 0.0;
  for (i = 0; i < 400; i++) {
    sum += A[i][i] * x[i] + y[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    z[i] = sum - A[i][i] * z[i];
  }
}