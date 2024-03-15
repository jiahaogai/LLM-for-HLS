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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 120; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double u_i;
    double v_i;
    double w_i;
    double Aij;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 120; j++) {
      u_i = u1[i];
      v_i = v1[i];
      w_i = w[j];
      Aij = A[i][j];
      tmp += Aij * u_i * v_i;
      tmp_x += Aij * v_i;
      tmp_y += Aij * u_i;
      x[j] += tmp_x * w_i;
      y[j] += tmp_y * w_i;
      z[i] += Aij * u_i * v_i;
    }
    z[i] = beta * z[i] + alpha * tmp;
    x[i] = x[i] + tmp_x;
    y[i] = y[i] + tmp_y;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 120; i++) {
    double x_i = x[i];
    double y_i = y[i];
    double u_ip1;
    double v_ip1;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double Aip1j;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (j = 0; j < 120; j++) {
      if (i < j) {
        Aip1j = A[i + 1][j];
        u_ip1 = u1[i + 1];
        v_ip1 = v1[i + 1];
        tmp_x += Aip1j * v_ip1;
        tmp_y += Aip1j * u_ip1;
        x[j] += tmp_x;
        y[j] += tmp_y;
      }
    }
    x[i] = x_i + tmp_x;
    y[i] = y_i + tmp_y;
    z[i] += x_i * u_i * v_i + y_i * v_i * u_i + x_i * v_ip1 * u_i + y_i * u_ip1 * v_i;
  }
}
