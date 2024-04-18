#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{120}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  kernel_vmv:
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
    kernel_vmv_A:
    for (j = 0; j < 400; j++) {
      y_1[i] += A[i][j] * x2[j];
    }
    kernel_vmv_x1:
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_2[j];
    }
  }
}