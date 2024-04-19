#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    double tmp = y_1[i];
    y_1[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{12}
    for (j = 0; j < 400; j++) {
      y_1[i] += A[i][j] * x1[j];
    }
    y_2[i] = tmp + x2[i] * y_1[i];
  }
}