#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][40],double x1[40],double x2[40],double y_1[40],double y_2[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 40; j++) {
      x1[j] += A[i][j] * x_1[i];
      y_1[i] += A[i][j] * x_2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 40; i++) {
    x2[i] = ((double )0);
    y_2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{24}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 40; j++) {
      x2[j] += A[i][j] * x_1[i];
      y_2[i] += A[i][j] * x_2[j];
    }
  }
}