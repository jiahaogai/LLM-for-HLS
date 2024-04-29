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
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
    for (row_up = row - 1; row_up >= 1; row_up--) {
      t = row_up * 32 + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{14}
      loop_col_up:
      for (col_up = 31; col_up >= 1; col_up--) {
        i = t + col_up;
        sol[i] = orig[i] + filter[0] * orig[i - 1] + filter[1] * (orig[i - 32] + orig[i + 32]) + filter[2] * orig[i + 1];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_down:
    for (row_down = row + 1; row_down < 33; row_down++) {
      t = row_down * 32 + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{14}
      loop_col_down:
      for (col_down = 0; col_down < 31; col_down++) {
        i = t + col_down;
        j = row_down * 32 + col_down + 1;
        sol[i] = orig[i] + filter[0] * orig[j - 1] + filter[1] * (orig[j - 32] + orig[j + 32]) + filter[2] * orig[j + 1];
      }
    }
  }
}