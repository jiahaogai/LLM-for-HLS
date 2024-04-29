#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_dw;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = ((i - 1) * 8);
      row_dw = ((i + 1) * 8);
      col = j * 8;
      col_left = ((j - 1) * 8);
      col_right = ((j + 1) * 8);
      t = filter[0] * orig[row + col] + filter[1] * (orig[row_up + col_left] + orig[row_up + col] + orig[row_up + col_right] + orig[row + col_left] + orig[row + col_right] + orig[row_dw + col_left] + orig[row_dw + col] + orig[row_dw + col_right]) + filter[2] * orig[row_dw + col];
      sol[row + col] = t;
    }
  }
}