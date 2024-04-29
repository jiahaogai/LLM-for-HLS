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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int bottom_row_boundary = 256 + 1;
      int top_row_boundary = 0 - 1;
      int left_col_boundary = 0 - 1;
      int right_col_boundary = 256 + 1;
      row_down = i + 1;
      row_up = i - 1;
      col_right = j + 1;
      col_left = j - 1;
      row = i;
      col = j;
      if (row_down < bottom_row_boundary) {
        t += orig[row_down * 256 + col] * filter[0];
      }
      if (row_up >= top_row_boundary) {
        t += orig[row_up * 256 + col] * filter[1];
      }
      if (col_right < right_col_boundary) {
        t += orig[row * 256 + col_right] * filter[2];
      }
      if (col_left >= left_col_boundary) {
        t += orig[row * 256 + col_left] * filter[3];
      }
      if (row_down < bottom_row_boundary && col_right < right_col_boundary) {
        t += orig[row_down * 256 + col_right] * filter[4];
      }
      if (row_up >= top_row_boundary && col_right < right_col_boundary) {
        t += orig[row_up * 256 + col_right] * filter[5];
      }
      if (row_down < bottom_row_boundary && col_left >= left_col_boundary) {
        t += orig[row_down * 256 + col_left] * filter[6];
      }
      if (row_up >= top_row_boundary && col_left >= left_col_boundary) {
        t += orig[row_up * 256 + col_left] * filter[7];
      }
      sol[i * 256 + j] = t;
    }
  }
}