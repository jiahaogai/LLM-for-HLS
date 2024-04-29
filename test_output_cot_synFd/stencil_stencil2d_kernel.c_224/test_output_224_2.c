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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      int filter_elem = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        row_up = i - 1 + filter_elem - 4;
        row_down = i + 1 + filter_elem - 4;
        if (row_up < 0) {
          row_up = 0;
        }
        if (row_down > 7) {
          row_down = 7;
        }
        col_left = j - 1 + filter_elem - 4;
        col_right = j + 1 + filter_elem - 4;
        if (col_left < 0) {
          col_left = 0;
        }
        if (col_right > 7) {
          col_right = 7;
        }
        row = row_down * 8 + col_right;
        t += filter[filter_elem] * orig[row];
      }
      sol[i * 8 + j] = t;
    }
  }
}