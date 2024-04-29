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
  for (i = 0; i < 8192; i++) {
    row = i & 127;
    row_up = (row - 1 + 128) % 128;
    row_down = (row + 1) % 128;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      col = j & 127;
      col_left = (col - 1 + 128) % 128;
      col_right = (col + 1) % 128;
      t = orig[i * 8192 + j] + filter[0] * orig[row_up * 8192 + col_left] + filter[1] * orig[row_up * 8192 + col] + filter[2] * orig[row_up * 8192 + col_right] + filter[3] * orig[row * 8192 + col_left] + filter[4] * orig[row * 8192 + col_right] + filter[5] * orig[row_down * 8192 + col_left] + filter[6] * orig[row_down * 8192 + col] + filter[7] * orig[row_down * 8192 + col_right];
      sol[i * 8192 + j] = t;
    }
  }
}