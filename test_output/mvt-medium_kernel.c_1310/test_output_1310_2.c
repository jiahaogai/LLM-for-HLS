#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    y_1[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x1[i] = x1[i] + A[i][j] * y_2[j];
    }
  }
  
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y_1[i] = x1[i] + A[i][499] * y_2[499];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
    y_2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x2[i] = x2[i] + A[j][i] * y_1[j];
    }
  }
  
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    y_2[i] = x2[i] + A[499][i] * y_1[499];
  }
}