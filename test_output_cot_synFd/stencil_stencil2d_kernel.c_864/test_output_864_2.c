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
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      int filter_elem;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        row_up = i - 8;
        row_down = i + 8;
        col_left = j - 8;
        col_right = j + 8;
        if (row_up < 0) {
          row_up = 0;
        }
        if (row_down > 8183) {
          row_down = 8183;
        }
        if (col_left < 0) {
          col_left = 0;
        }
        if (col_right > 8183) {
          col_right = 8183;
        }
        row = row_up;
        while (row <= row_down) {
          col = col_left;
          while (col <= col_right) {
            t += orig[row * 8192 + col] * filter[filter_elem];
            col += 8;
          }
          row += 8;
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}