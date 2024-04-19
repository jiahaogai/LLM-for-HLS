#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double y_1[400],double x_1[400],double y_2[400],double x_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x_1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x_1[j] += A[i][j] * y_1[i];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    x_2[i] = 0.0;
    for (j = 0; j < 400; j++) {
      x_2[i] += A[j][i] * y_2[j];
    }
  }
}