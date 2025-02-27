#include <math.h>
#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner_3:
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        inner_2:
        for (k_row = -4; k_row < 5; k_row++) {
          k = (8192 * (k_row + 4)) + (k_col + 4);
          sum += filter[(((k_row + 4) * 9) + (k_col + 4)) ] * orig[k];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}