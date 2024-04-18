c
 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 400; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double du = 0.0;
    double dv = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      du += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * v2[j];
      dv += A[i][j] * u2[j];
    }
    z[i] = tmp1 + du * alpha + beta * y[i];
    w[i] = tmp2 + dv * alpha;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    double x_i = 0.0;
    double y_i = 0.0;
    
#pragma ACCEL PARALLEL reduction=x_i FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      x_i += A[j][i] * y[j];
    }
    
#pragma ACCEL PARALLEL reduction=y_i FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      y_i += A[j][i] * x[j];
    }
    x[i] = x_i;
    y[i] = y_i;
  }
}