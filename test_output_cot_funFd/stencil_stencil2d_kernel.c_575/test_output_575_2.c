#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  int t_col;
  int j_row;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; ++k) {
        k_col = k + ((-4) + i);
        i_col = ((-4) + i) + ((-4) + k_col);
        j_col = j + k_col;
        t_col = orig[i_col] * filter[k];
        sol[j_col] = t + t_col;
        t = t_col;
      }
    }
    j_row = i + 4;
    
#pragma ACCEL PARALLEL reduction=j_row FACTOR=auto{8}
    outer_row:
    for (j = 0; j < 64; ++j) {
      orig[j_row] = sol[j];
      j_row += 8;
    }
  }
}