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
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (row = -1 + i; row < i + 8 - 1; ++row) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = -1 + j; col < j + 8 - 1; ++col) {
          row_up = row - 1;
          row_down = row + 1;
          col_left = col - 1;
          col_right = col + 1;
          if (row_up < -1 + i) {
            row_up = -1 + i;
          }
          if (row_down > i + 7 - 1) {
            row_down = i + 7 - 1;
          }
          if (col_left < -1 + j) {
            col_left = -1 + j;
          }
          if (col_right > j + 7 - 1) {
            col_right = j + 7 - 1;
          }
          t += ((orig[row_down * 8 + col_right] + orig[row_down * 8 + col_left] + orig[row_up * 8 + col_left] + orig[row_up * 8 + col_right] - orig[row * 8 + col_right] - orig[row * 8 + col_left] - orig[row_down * 8 + col] - orig[row_up * 8 + col]) * filter[4]) / 81;
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}