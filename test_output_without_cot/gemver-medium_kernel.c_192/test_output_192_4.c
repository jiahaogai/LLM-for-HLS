#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
    }
    x[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * v1[j];
    }
    y[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      tmp += A[j][i] * u2[j];
    }
    z[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 400; i++) {
    w[i] = beta * w[i] + y[i] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 400; i++) {
    double tmp_x = 0.0;
#pragma ACCEL PARALLEL reduction=tmp_x FACTOR=auto{__PARA__L8}
    for (j = 0; j < 400; j++) {
      tmp_x += A[i][j] * x[j];
    }
    double tmp_y = 0.0;
#pragma ACCEL PARALLEL reduction=tmp_y FACTOR=auto{__PARA__L9}
    for (j = 0; j < 400; j++) {
      tmp_y += A[j][i] * y[j];
    }
    A[i][i] = alpha * (x[i] + y[i] + z[i]) - tmp_x - tmp_y;
  }
}