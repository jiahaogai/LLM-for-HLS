#pragma ACCEL kernel

void kernel_mvt(int n,double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * y_1[j];
    }
    x1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * y_2[j];
    }
    x2[i] = sum;
  }
}