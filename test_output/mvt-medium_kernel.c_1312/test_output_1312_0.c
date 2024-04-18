#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    double x_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=x_tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * y_1[j];
    }
    x_tmp = sum;
    x1[i] = x_tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    double y_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=y_tmp FACTOR=auto{15}
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * x1[j];
    }
    y_tmp = sum;
    x2[i] = y_tmp;
  }
}