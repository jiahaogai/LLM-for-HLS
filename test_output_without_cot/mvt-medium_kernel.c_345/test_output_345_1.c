#include <math.h>
#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{5}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
}