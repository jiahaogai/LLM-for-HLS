
 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 120; i++) {
    x[i] = ((double )0);
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 120; i++) {
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    double u_entry = u1[i];
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 120; j++) {
      double A_entry = A[i][j];
      double v_entry = v1[j];
      tmp_x += A_entry * v_entry;
      tmp_y += A_entry * u_entry;
      tmp_z += A_entry * v_entry * u_entry;
    }
    x[i] = alpha * tmp_x;
    y[i] = alpha * tmp_y;
    z[i] = beta * tmp_z + y[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 120; i++) {
    double tmp_x = ((double )0);
    double tmp_y = ((double )0);
    double u_entry = u2[i];
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 120; j++) {
      double A_entry = A[j][i];
      double v_entry = v2[j];
      tmp_x += A_entry * v_entry;
      tmp_y += A_entry * u_entry;
    }
    x[i] += tmp_x;
    y[i] += alpha * 2.0 * u_entry * v2[i] + tmp_y;
  }
}
