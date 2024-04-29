#pragma ACCEL kernel

#include <math.h>

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 33; j++) {...} */
  for (j = 0 + 1; j < 33 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j + (-1 + k_col);
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loopk:
      for (k = 0; k < 9; k++) {
        i = i_col + (-1 + k);
        sum += filter[k] * orig[i];
      }
      sol[j] = sum;
    }
  }
}