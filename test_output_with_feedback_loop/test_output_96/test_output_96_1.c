#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[50],double x[40],double y[40],double z[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double Ai_j[50];
    for (j = 0; j < 50; j++) {
      Ai_j[j] = A[i][j];
      tmp_x += A[i][j] * x[j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      tmp += Ai_j[j] * y[j];
      tmp_y += Ai_j[j] * u1[j];
    }
    z[i] = tmp_x;
    double Bj = beta * v1[i] + alpha * tmp;
    y[i] = Bj;
    double Ci = beta * u2[i] + alpha * tmp_y;
    for (j = 0; j < 50; j++) {
      w[j] += A[i][j] * Bj;
    }
    x[i] = Ci;
  }
}