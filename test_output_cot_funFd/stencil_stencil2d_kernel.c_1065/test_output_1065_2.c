#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int index_up;
  int index_down;
  int index_left;
  int index_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8192; j += 8) {
      tmp_orig = 0;
      tmp_sol = 0;
      index_up = i - 8;
      index_down = i + 8;
      index_left = j - 8;
      index_right = j + 8;
      // Up
      if (index_up < 0) {
        index_up = 0;
      }
      // Down
      if (index_down > 8184) {
        index_down = 8184;
      }
      // Left
      if (index_left < 0) {
        index_left = 0;
      }
      // Right
      if (index_right > 8192) {
        index_right = 8192;
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_up:
      for (k = index_up; k < index_down; k++) {
        tmp = orig[k * 8192 + j];
        tmp_orig += filter[0] * tmp;
        tmp_sol += filter[0] * sol[k * 8192 + j];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_left:
      for (k = index_left; k < index_right; k++) {
        tmp = orig[i * 8192 + k];
        tmp_orig += filter[1] * tmp;
        tmp_sol += filter[1] * sol[i * 8192 + k];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_down:
      for (k = index_down; k < index_up + 1; k++) {
        tmp = orig[k * 8192 + j];
        tmp_orig += filter[2] * tmp;
        tmp_sol += filter[2] * sol[k * 8192 + j];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_right:
      for (k = index_right; k < index_left + 1; k++) {
        tmp = orig[i * 8192 + k];
        tmp_orig += filter[3] * tmp;
        tmp_sol += filter[3] * sol[i * 8192 + k];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_middle:
      for (k = 4; k < 9 - 1; k++) {
        tmp = orig[i * 8192 + j + k - 4];
        tmp_orig += filter[k] * tmp;
        tmp_sol += filter[k] * sol[i * 8192 + j + k - 4];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_update:
      sol[i * 8192 + j] = tmp_sol / tmp_orig;
    }
  }
}