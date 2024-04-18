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
//#pragma scop
/* Ai = A[i] */
    Ai = A[i][0];
/* tmp_x = u1[i] * A[i] * v1[i] */
    u1_i = u1[i];
    v1_i = v1[i];
    tmp_x = u1_i * Ai * v1_i;
/* tmp_y = u2[i] * A[i] * v2[i] */
    Ai = A[i][1];
    u1_i = u2[i];
    v1_i = v2[i];
    tmp_y = u1_i * Ai * v1_i;
/* tmp_z = u1[i] * A[i] * v1[i] + u2[i] * A[i] * v2[i] */
    Ai = A[i][2];
    u1_i = u1[i];
    v1_i = v1[i];
    tmp_z = u1_i * Ai * v1_i + u2[i] * Ai * v2[i];
/* z[i] = beta*z[i] + alpha*tmp */
    z[i] = beta * z[i] + alpha * tmp;
/* x[i] = beta*x[i] + alpha*tmp_x */
    x[i] = beta * x[i] + alpha * tmp_x;
/* y[i] = beta*y[i] + alpha*tmp_y */
    y[i] = beta * y[i] + alpha * tmp_y;
/* w[i] = beta*w[i] + alpha*tmp_z */
    w[i] = beta * w[i] + alpha * tmp_z;
/* A[i] = A[i] + u1[i] * tmp_x + u2[i] * tmp_y */
    A[i][0] = A[i][0] + u1_i * tmp_x + u2_i * tmp_y;
/* A[i + 1] = A[i + 1] + u1[i] * tmp_y + u2[i] * tmp_x */
    A[i][1] = A[i][1] + u1_i * tmp_y + u2_i * tmp_x;
/* A[i + 2] = A[i + 2] + u1[i] * tmp_z + u2[i] * tmp_x */
    A[i][2] = A[i][2] + u1_i * tmp_z + u2_i * tmp_x;
  }
//#pragma endscop
}