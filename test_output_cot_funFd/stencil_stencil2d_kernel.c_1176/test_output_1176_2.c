#pragma ACCEL kernel

#include <math.h>

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) to: for(int j... ) */
  for(int j = 1;j < 33;j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for(int k = 1;k < 33;k++) {
      i = k + ((j - 1) * 32);
      idx = 4 + filter[0] * i + filter[1] * (i + 32) + filter[2] * (i + 32 * 32);
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopk2:
      for(int k2 = 0;k2 < 3;k2++) {
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
        loopj2:
        for(int j2 = 0;j2 < 3;j2++) {
          val += orig[idx + filter[j2 + 1] * (32 * (k2 + 1)) + filter[j2 + 4] * 1] * filter[j2 + 4];
        }
      }
      sol[i] = val;
    }
  }
}