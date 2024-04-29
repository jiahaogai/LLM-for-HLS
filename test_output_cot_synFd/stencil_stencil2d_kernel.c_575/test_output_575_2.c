#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 1; k_col < 33 - 1; k_col++) {
      col = j * (33 - 2) + k_col;
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 1; k_row < 33 - 1; k_row++) {
        row = (33 - 2) * j + k_row;
        k = k_row * (33 - 2) + k_col;
        sol[row] = ((filter[k_row * 33 + k_col] * orig[row]) + ((32 - filter[k_row * 33 + k_col]) * sol[row]));
      }
    }
  }
}