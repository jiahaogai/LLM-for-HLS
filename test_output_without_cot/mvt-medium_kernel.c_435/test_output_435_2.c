#pragma ACCEL kernel

void kernel_mvt(int n,double A[40][50],double x1[40],double x2[50],double y_1[40],double y_2[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    x1[i] = 0.0;
    y_1[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      x1[i] += A[i][j] * x2[j];
      y_1[i] += A[i][j] * y_2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 50; i++) {
    x2[i] = 0.0;
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      x2[i] += A[j][i] * x1[j];
      y_2[i] += A[j][i] * y_1[j];
    }
  }
}