c
 #pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    double x_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{5}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x1[j];
    }
    x_tmp = sum + y_1[i];
    x1[i] = x_tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    double y_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{24}
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * x1[j];
    }
    y_tmp = sum + y_2[i];
    x2[i] = y_tmp;
  }
}