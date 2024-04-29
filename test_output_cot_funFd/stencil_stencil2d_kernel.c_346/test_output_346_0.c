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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
    for (row_up = row - 1; row_up > 0; row_up--) {
      t = row_up * 32 + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{14}
      loop_col_left:
      for (col_left = 1; col_left < 32 + 1; col_left++) {
        sol[t + col_left] = orig[t + col_left] + filter[0] * orig[t + col_left - 1] + filter[1] * orig[t + col_left] + filter[2] * orig[t + col_left + 1] + filter[3] * orig[t + col_left - 32] + filter[4] * orig[t + col_left + 32];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_down:
    for (row_down = row + 1; row_down < 33; row_down++) {
      t = row_down * 32 + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{14}
      loop_col_right:
      for (col_right = 0; col_right < 32 - 1; col_right++) {
        sol[t + col_right] = orig[t + col_right] + filter[0] * orig[t + col_right - 1] + filter[1] * orig[t + col_right] + filter[2] * orig[t + col_right + 1] + filter[3] * orig[t + col_right - 32] + filter[4] * orig[t + col_right + 32];
      }
    }
  }
}