#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double v1[400],double v2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    y_1[i] = 0.0;
    y_2[i] = 0.0;
    for (j = 0; j < 400; j++) {
      y_1[i] += A[i][j] * v1[j];
      y_2[i] += A[i][j] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 400; i++) {
    v1[i] = y_1[i];
    v2[i] = y_2[i];
  }
}