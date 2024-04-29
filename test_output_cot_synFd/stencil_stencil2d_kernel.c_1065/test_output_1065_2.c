#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loopj:
  for (j = 8; j < 8184; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 8; i < 8184; i++) {
      t = 0;
      row_up = (j - 8 + 8192) % 8192;
      row_down = (j + 8) % 8192;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loopk:
      for (k = 8; k < 8192; k++) {
        col_left = (k - 8 + 8192) % 8192;
        col_right = (k + 8) % 8192;
        t += filter[0] * orig[row_up * 8192 + col_left];
        t += filter[1] * orig[row_up * 8192 + k];
        t += filter[2] * orig[row_up * 8192 + col_right];
        t += filter[3] * orig[row_down * 8192 + col_left];
        t += filter[4] * orig[row_down * 8192 + k];
        t += filter[5] * orig[row_down * 8192 + col_right];
        t += filter[6] * orig[j * 8192 + col_left];
        t += filter[7] * orig[j * 8192 + k];
        t += filter[8] * orig[j * 8192 + col_right];
      }
      sol[j * 8192 + i] = t;
    }
  }
}