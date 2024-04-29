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
      t = filter[0] * orig[row_up * 8 + col_left] + filter[1] * orig[row_up * 8 + j] + filter[2] * orig[row_up * 8 + col_right] + filter[3] * orig[i * 8 + col_left] + filter[4] * orig[i * 8 + j] + filter[5] * orig[i * 8 + col_right] + filter[6] * orig[row_down * 8 + col_left] + filter[7] * orig[row_down * 8 + j] + filter[8] * orig[row_down * 8 + col_right];
      sol[i * 8 + j] = t;
    }
  }
}