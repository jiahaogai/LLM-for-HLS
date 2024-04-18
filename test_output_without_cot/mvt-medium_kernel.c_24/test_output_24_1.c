#include <math.h>
#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
  }
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
//#pragma endscop
}