#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int border;
  int center;
  border = 4;
  center = 2048;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      int sum = 0;
      int val;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        val = orig[i * 256 + j + k];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int l = 0; l < 9; l++) {
          sum += val * filter[l];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}