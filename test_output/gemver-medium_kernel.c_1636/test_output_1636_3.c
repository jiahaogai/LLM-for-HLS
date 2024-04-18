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
      tmp4 += A_ii + alpha * (z_i - w_i);
      tmp5 += u_i + v_i;
      tmp6 += x_i + y_i;
    }
    A[i][i] = tmp4;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400 - 1; j++) {
      A_i_j = A[i][j + 1];
      x_i = x[i] * v2[j + 1];
      y_i = y[i] * u2[j + 1];
      z_i = z[i] * u2[j + 1];
      A[i][j + 1] = A_i_j + x_i + y_i;
    }
    A[i][400 - 1] = A[i][400 - 1] + tmp6;
    u1[i] = tmp5;
    v1[i] = tmp1;
    w[i] = tmp3;
    x[i] = tmp2;
    y[i] = tmp1 + beta * z[i];
  }
}