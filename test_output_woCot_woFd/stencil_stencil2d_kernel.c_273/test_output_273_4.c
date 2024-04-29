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
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 64;
      row_up = row - 1;
      row_down = row + 1;
      col = j * 8;
      col_left = col - 1;
      col_right = col + 1;
      t = orig[row + col] + filter[0] * orig[row_up + col_left] + filter[1] * orig[row_up + col] + filter[2] * orig[row_up + col_right] + filter[3] * orig[row + col_left] + filter[4] * orig[row + col_right] + filter[5] * orig[row_down + col_left] + filter[6] * orig[row_down + col] + filter[7] * orig[row_down + col_right];
      sol[row + col] = t;
    }
  }
}