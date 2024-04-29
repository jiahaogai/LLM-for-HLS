#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction = orig FACTOR=auto{1}
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[i + k * 8192];
      }
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      sol[i * 8192 + j] = t;
    }
  }
}