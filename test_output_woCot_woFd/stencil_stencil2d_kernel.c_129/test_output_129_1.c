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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
        i = row_up;
        if (t == 4) {
          i = row;
        }
        j = col_left;
        if (t == 4) {
          j = col;
        }
        if (i > 0 && i < 8191 && j > 0 && j < 8191) {
          t += filter[t] * orig[i * 8192 + j];
        }
      }
      sol[row * 8192 + col] = t;
    }
  }
}