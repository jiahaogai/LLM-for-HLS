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
  loopj:
  for (j = 8; j < 9008; j++) {
    row = j - 8;
    row_up = (row - 1) < 0 ? 0 : row - 1;
    row_down = row + 1 > 9000 ? 9000 : row + 1;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    loopi:
    for (i = 8; i < 9008; i++) {
      col = i - 8;
      col_left = (col - 1) < 0 ? 0 : col - 1;
      col_right = col + 1 > 9000 ? 9000 : col + 1;
      t = orig[row * 9000 + col] + filter[0] * orig[row_up * 9000 + col_left] + filter[1] * orig[row_up * 9000 + col] + filter[2] * orig[row_up * 9000 + col_right] + filter[3] * orig[row * 9000 + col_left] + filter[4] * orig[row * 9000 + col_right] + filter[5] * orig[row_down * 9000 + col_left] + filter[6] * orig[row_down * 9000 + col] + filter[7] * orig[row_down * 9000 + col_right];
      sol[row * 9000 + col] = t;
    }
  }
}