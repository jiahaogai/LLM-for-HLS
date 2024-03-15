#pragma ACCEL kernel

void kernel_mvt(double x[4096],double y[4096],double A[4096][32],double B[4096][32])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
    for (j = 0; j < 4096; j++) {
      y[i] += A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4096; i++) {
    x[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L2}
    for (j = 0; j < 32; j++) {
      x[i] += B[i][j] * y[j];
    }
  }
}