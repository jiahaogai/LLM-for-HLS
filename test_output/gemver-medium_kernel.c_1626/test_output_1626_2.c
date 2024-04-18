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
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
    }

    tmp_x = tmp * v1[i];
    
#pragma ACCEL PARALLEL reduction=tmp_x FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp_x += A[i][j] * v2[j] * y[j];
    }

    x[i] = alpha * tmp_x + beta * x[i];
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      x[i] += A[i][j] * u2[j] * y[j];
    }

    tmp_y = tmp * v1[i];
    
#pragma ACCEL PARALLEL reduction=tmp_y FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp_y += A[i][j] * u1[j] * z[j];
    }

    y[i] = alpha * tmp_y + beta * y[i];
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      y[i] += A[i][j] * v2[j] * x[j];
    }

    tmp_z = tmp * v2[i];
    
#pragma ACCEL PARALLEL reduction=tmp_z FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      tmp_z += A[i][j] * u2[j] * z[j];
    }

    z[i] = alpha * tmp_z + beta * z[i];
  }
}