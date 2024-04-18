#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  gemv_1:
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
    gemv_2:
    for (j = 0; j < 400; j++) {
      x[i] += alpha * A[i][j] * u1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  gemv_3:
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L3}
    gemv_4:
    for (j = 0; j < 400; j++) {
      y[i] += beta * A[i][j] * v1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  gemv_5:
  for (i = 0; i < 400; i++) {
    z[i] = beta * y[i] + z[i];
    qrt_1:
    for (j = 0; j < 400; j++) {
      w[i] += A[i][j] * u2[j] * v2[j];
    }
  }
}