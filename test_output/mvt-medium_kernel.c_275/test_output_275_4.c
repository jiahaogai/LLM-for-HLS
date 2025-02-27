#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x1[i] += A[j][i] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{16}
    for (j = 0; j < 400; j++) {
      y_2[i] += A[i][j] * x1[j];
    }
  }
}