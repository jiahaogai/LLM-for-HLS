#include <math.h>
#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
  ;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y_1[i] = 0.0;
    y_2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y_1 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      y_1[i] += A[i][j] * x1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      y_2[i] += A[i][j] * x2[j];
    }
  }
}