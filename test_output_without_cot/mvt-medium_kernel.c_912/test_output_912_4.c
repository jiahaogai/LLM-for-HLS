c
 #pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x1[j];
    }
    y_1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * y_1[j];
    }
    x2[i] = sum;
  }
}