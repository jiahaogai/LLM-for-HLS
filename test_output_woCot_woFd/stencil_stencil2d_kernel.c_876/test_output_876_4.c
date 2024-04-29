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
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      row_up = (i - 1 < 0) ? 0 : i - 1;
      row_down = (i + 1 > 127) ? 127 : i + 1;
      col_left = (j - 1 < 0) ? 0 : j - 1;
      col_right = (j + 1 > 127) ? 127 : j + 1;
      t = filter[0] * orig[row_up * 128 + col_left] + filter[1] * orig[row_up * 128 + j] + filter[2] * orig[row_up * 128 + col_right] + filter[3] * orig[row_down * 128 + col_left] + filter[4] * orig[row_down * 128 + j] + filter[5] * orig[row_down * 128 + col_right] + filter[6] * orig[row * 128 + col_left] + filter[7] * orig[row * 128 + col_right] + filter[8] * orig[row_down * 128 + col_down];
      sol[i * 128 + j] = t;
    }
  }
}