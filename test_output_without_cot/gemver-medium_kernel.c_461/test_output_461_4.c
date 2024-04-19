#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp4 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * u2[j];
      tmp3 += A[i][j] * v2[j];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
    
#pragma ACCEL PARALLEL reduction=x[i] FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      x[i] += alpha * (A[i][j] * u1[j] + v1[j] * tmp1);
    }
    
#pragma ACCEL PARALLEL reduction=z[i] FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i] += alpha * A[i][j] * u2[j] + beta * (y[j] * v2[j] + tmp2 + w[j] * tmp4);
    }
  }
}