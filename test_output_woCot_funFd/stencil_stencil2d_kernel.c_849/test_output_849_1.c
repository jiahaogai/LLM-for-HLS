#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    for (col = 1; col < 8191; col++) {
      t = 0;
      row_up = row - 1;
      row_down = row + 1;
      col_left = col - 1;
      col_right = col + 1;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_t:
      for (t = 0; t < 9; t++) {
        i = row_up + ((4 - 1) + 2 * t);
        j = col_left + ((4 - 1) + 2 * t);
        if (i < 0 || 8191 < i || j < 0 || 8191 < j) {
          continue;
        }
        t = filter[t] * orig[i * 8192 + j];
      }
      sol[row * 8192 + col] = t;
    }
  }
}