c
 #pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * y_1[j];
      x1[i] += A[i][j] * y_1[j];
    }
    y_2[i] = tmp;
  }
}