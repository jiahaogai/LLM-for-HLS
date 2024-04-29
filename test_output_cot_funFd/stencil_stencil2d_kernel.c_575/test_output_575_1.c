#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 31 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 9; k_col++) {
      k_row = k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      /* Standardize from: for(k ... ) */
      for (k = 1; k < 31 + 1 - 1; k++) {
        if (k_row < 9) {
          k_row++;
          continue;
        }
        idx = (31 * (j - 1) + (k - 1));
        s = 0;
        loopfilter:
        for (i = 0; i < 9; i++) {
          s += orig[idx + i - 1] * filter[i];
        }
        sol[idx] = s;
      }
    }
  }
}