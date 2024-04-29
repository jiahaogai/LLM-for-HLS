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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_left = j * 8 - 1;
      col_right = j * 8 + 1;
      t = filter[0] * orig[row + col] + filter[1] * (orig[row_up + col_left] + orig[row_up + col] + orig[row_up + col_right] + orig[row + col_left] + orig[row + col_right] + orig[row_down + col_left] + orig[row_down + col] + orig[row_down + col_right]) + filter[2] * orig[row_down + col];
      sol[row + col] = t;
    }
  }
}