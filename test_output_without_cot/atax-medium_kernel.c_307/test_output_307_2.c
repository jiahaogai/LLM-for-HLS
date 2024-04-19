#include <math.h>
#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    y[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 390; i++) {
    tmp[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L2}
    for (j = 0; j < 410; j++) {
      tmp[i] += A[i][j] * x[j];
    }
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L3}
    for (j = 0; j < 410; j++) {
      y[j] += A[i][j] * tmp[i];
    }
  }
}