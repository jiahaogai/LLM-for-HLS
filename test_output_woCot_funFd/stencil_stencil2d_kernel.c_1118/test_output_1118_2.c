#include <math.h>
#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 4; l++) {
          sol[i][j] += filter[k][l] * orig[i + k][j + l];
        }
      }
    }
  }
//#pragma endscop
}