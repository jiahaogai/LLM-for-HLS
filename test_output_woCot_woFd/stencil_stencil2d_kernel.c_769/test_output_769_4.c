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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = row - 1;
      row_down = row + 1;
      col = j * 8;
      col_left = col - 1;
      col_right = col + 1;
      t = orig[row * 64 + col] + filter[0] * (orig[row_up * 64 + col_left] + orig[row_up * 64 + col] + orig[row_up * 64 + col_right] + orig[row * 64 + col_left] + orig[row * 64 + col_right] + orig[row_down * 64 + col_left] + orig[row_down * 64 + col] + orig[row_down * 64 + col_right]) + filter[1] * (orig[row_left * 64 + col_up] + orig[row_left * 64 + col] + orig[row_left * 64 + col_down] + orig[row * 64 + col_up] + orig[row * 64 + col_down] + orig[row_right * 64 + col_up] + orig[row_right * 64 + col] + orig[row_right * 64 + col_down]) + filter[2] * (orig[row_up * 64 + col_left] + orig[row_up * 64 + col] + orig[row_up * 64 + col_right] + orig[row_down * 64 + col_left] + orig[row_down * 64 + col] + orig[row_down * 64 + col_right] + orig[row * 64 + col_left] + orig[row * 64 + col_right] + orig[row_left * 64 + col_up] + orig[row_left * 64 + col] + orig[row_left * 64 + col_down] + orig[row_right * 64 + col_up] + orig[row_right * 64 + col] + orig[row_right * 64 + col_down]);
      sol[row * 64 + col] = t;
    }
  }
}