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
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp_x += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=x[i] FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[i][j] * v2[j];
    }
    
#pragma ACCEL PARALLEL reduction=y[i] FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      y[i] += alpha * u2[j] * tmp_x + alpha * v2[j] * tmp;
    }
    
#pragma ACCEL PARALLEL reduction=z[i] FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i] += beta * A[i][j] * u1[j];
    }
  }
}