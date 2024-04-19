#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double y_1[400],double y_2[400],double x_1[400],double x_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x_1[i] = ((double )0);
    x_2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x_1[i] = x_1[i] + A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 400; i++) {
    x_2[i] = y_2[i] + 1.0 * x_1[i];
  }
}