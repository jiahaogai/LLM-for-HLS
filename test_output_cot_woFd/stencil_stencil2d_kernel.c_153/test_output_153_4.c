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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row_up = (i == 0 ? 0 : i - 1);
      row_down = (i == 7 ? 7 : i + 1);
      col_left = (j == 0 ? 0 : j - 1);
      col_right = (j == 7 ? 7 : j + 1);
      t = filter[0] * orig[row_up * 8 + col_left] + filter[1] * orig[row_up * 8 + j] + filter[2] * orig[row_up * 8 + col_right] + filter[3] * orig[row_down * 8 + col_left] + filter[4] * orig[row_down * 8 + j] + filter[5] * orig[row_down * 8 + col_right] + filter[6] * orig[row * 8 + col_left] + filter[7] * orig[row * 8 + col_right] + filter[8] * orig[row_down * 8 + col_down];
      sol[row_up * 8 + col_left] = t;
    }
    row = i * 8;
    inner:
    for (j = 0; j < 8; j++) {
      t = filter[0] * sol[row_up * 8 + j] + filter[1] * sol[row_up * 8 + col_right] + filter[2] * sol[row * 8 + j] + filter[3] * sol[row * 8 + col_right] + filter[4] * sol[row_down * 8 + j] + filter[5] * sol[row_down * 8 + col_right] + filter[6] * sol[row_down * 8 + col_left] + filter[7] * sol[row * 8 + col_left] + filter[8] * sol[row_down * 8 + col_down];
      sol[row * 8 + j] = t;
    }
  }
}