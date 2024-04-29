`sol` after dividing it by 4.

---

#include <math.h>
#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int k;
  int r_up;
  int r_down;
  int c_left;
  int c_right;
  double t;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 2; r <= 128 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 2; c <= 64 - 1; c++) {
      sum = 0.0;
      int k_col = -1;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k3:
      for (k = 0; k < 3; k++) {
        int k_row = -1;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_k2:
        for (k_row = 0; k_row < 3; k_row++) {
          int i = r + k_row;
          int j = c + k_col;
          if (i >= 0 && i < 128 && j >= 0 && j < 64) {
            sum += filter[k_row * 3 + k_col] * orig[i * 64 + j];
          }
        }
        k_col += 1;
      }
      t = sum / 4.0;
      sol[r * 64 + c] = t;
    }
    r_down = r + 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_r_down:
    for (r = r_down; r <= 128 - 1; r++) {
      sol[r * 64 + c] = sol[r_up * 64 + c];
    }
    r_up = r - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_c_down:
  for (c = 64 - 1; c >= 2; c--) {
    sol[r_up * 64 + c] = sol[r_up * 64 + c_right];
    c_left = c - 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c_left:
    for (c = c_left; c >= 2; c--) {
      sum = 0.0;
      int k_col = -1;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k3_1:
      for (k = 0; k < 3; k++) {
        int k_row = -1;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_k2_1:
        for (k_row = 0; k_row < 3; k_row++) {
          int i = r_up + k_row;
          int j = c + k_col;
          if (i >= 0 && i < 128 && j >= 0 && j < 64) {
            sum += filter[k_row * 3 + k_col] * orig[i * 64 + j];
          }
        }
        k_col += 1;
      }
      t = sum / 4.0;
      sol[r_up * 64 + c] = t;
    }
  }
}