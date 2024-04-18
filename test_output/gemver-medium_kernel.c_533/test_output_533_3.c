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
/* Standardize from: gemv.c */
/* A := A + u1 * v1' */
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      u1_i = u1[i] * v1[j];
      tmp += Ai * u1_i;
      A[i][j] = Ai + u1_i;
    }
/* x := x + beta * tmp */
    x[i] = ((beta * tmp) + x[i]);
/* A := A + u2 * v2' */
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      u1_i = u2[i] * v2[j];
      tmp_x += Ai * u1_i;
      A[i][j] = Ai + u1_i;
    }
/* y := y + beta * tmp_x */
    y[i] = ((beta * tmp_x) + y[i]);
/* A := A + x * y' */
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      v1_i = v1[j] * x[i];
      tmp_y += Ai * v1_i;
      A[i][j] = Ai + v1_i;
    }
/* z := z + alpha * tmp_y */
    z[i] = (alpha * tmp_y) + z[i];
/* End gemv */
//#pragma endscop
  }
}