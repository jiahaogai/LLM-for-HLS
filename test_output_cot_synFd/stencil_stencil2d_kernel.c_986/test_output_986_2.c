#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_i;
  int flatten_j;
  int bound;
  int bound_up;
  int bound_down;
  int bound_left;
  int bound_right;
  int orig_row_col;
  int sol_row_col;
  int filter_row_col;
  bound = 32;
  bound_up = bound - 1;
  bound_down = 0;
  bound_left = bound - 1;
  bound_right = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj_up:
  for (j = bound_up; j < 8; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_up:
    for (i = bound_up; i < 8; i++) {
      orig_row_col = ((8 * bound_up) + i) * 64 + (8 * bound_up) + j;
      sol_row_col = ((8 * bound) + i) * 64 + (8 * bound) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_up:
      for (k = 0; k < 9; k++) {
        filter_row_col = (8 * (k - 4)) + j;
        sol[sol_row_col] += orig[orig_row_col] * filter[filter_row_col];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_down:
  for (j = bound_down; j < 7 - bound_down; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_down:
    for (i = bound_down; i < 7 - bound_down; i++) {
      orig_row_col = ((8 * bound_down) + i) * 64 + (8 * bound_down) + j;
      sol_row_col = ((8 * bound) + i) * 64 + (8 * bound) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk_down:
      for (k = 0; k < 9; k++) {
        filter_row_col = (8 * (k - 4)) + j;
        sol[sol_row_col] += orig[orig_row_col] * filter[filter_row_col];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_left:
  for (j = bound_left; j < 8 - bound_left; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_left:
    for (i = bound_left; i < 8 - bound_left; i++) {
      orig_row_col = ((8 * bound_left) + i) * 64 + (8 * bound_left) + j;
      sol_row_col = ((8 * bound) + i) * 64 + (8 * bound) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk_left:
      for (k = 0; k < 9; k++) {
        filter_row_col = (8 * (k - 4)) + j;
        sol[sol_row_col] += orig[orig_row_col] * filter[filter_row_col];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_right:
  for (j = bound_right; j < 7 - bound_right; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_right:
    for (i = bound_right; i < 7 - bound_right; i++) {
      orig_row_col = ((8 * bound_right) + i) * 64 + (8 * bound_right) + j;
      sol_row_col = ((8 * bound) + i) * 64 + (8 * bound) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_right:
      for (k = 0; k < 9; k++) {
        filter_row_col = (8 * (k - 4)) + j;
        sol[sol_row_col] += orig[orig_row_col] * filter[filter_row_col];
      }
    }
  }
}