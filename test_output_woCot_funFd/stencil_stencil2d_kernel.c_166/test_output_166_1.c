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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 64;
      row_up = row - 1;
      row_down = row + 1;
      col = j * 8;
      col_left = col - 1;
      col_right = col + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (t = 0; t < 9; t++) {
        if ((((row_up >= 0) && (col_left >= 0)) && (a[row_up][col_left] != 0)) || (((row_up >= 0) && (col < 64)) && (a[row_up][col] != 0)) || (((row_up >= 0) && (col_right < 8)) && (a[row_up][col_right] != 0)) || (((row < 64) && (col_left >= 0)) && (a[row][col_left] != 0)) || (((row < 64) && (col_right < 8)) && (a[row][col_right] != 0)) || (((row_down < 8) && (col_left >= 0)) && (a[row_down][col_left] != 0)) || (((row_down < 8) && (col < 64)) && (a[row_down][col] != 0)) || (((row_down < 8) && (col_right < 8)) && (a[row_down][col_right] != 0))) {
          t += filter[t];
        }
      }
      sol[row * 8 + col] = t;
    }
  }
}