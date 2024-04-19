#pragma ACCEL kernel

void kernel_mvt(double x[4096],double y[4096],double A[4096][8000],double B[4096][8000])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4096; i++) {
    x[i] = 0.0;
    for (j = 0; j < 8000; j++) {
      x[i] += A[i][j] * B[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4096; i++) {
    y[i] = 0.0;
    for (j = 0; j < 8000; j++) {
      y[i] += B[i][j] * A[i][j];
    }
  }
}