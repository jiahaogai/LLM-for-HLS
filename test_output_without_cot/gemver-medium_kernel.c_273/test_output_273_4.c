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
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp2 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp3 += A[i][j] * u2[j];
    }
    
#pragma ACCEL PARALLEL reduction=x[i] FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      x[i] += alpha * A[i][j] * v2[j] + tmp1 * v1[j] + tmp2 * u1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp4 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp4 += A[i][j] * v2[j];
    }
    
#pragma ACCEL PARALLEL reduction=y[i] FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      y[i] += beta * w[j] + z[j] * x[i] + tmp3 * v2[j] + u1[i] * tmp4;
    }
  }
}