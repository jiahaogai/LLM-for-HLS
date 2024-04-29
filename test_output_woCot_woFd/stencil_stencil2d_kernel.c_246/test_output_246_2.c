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
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_up = (j - 1) * 8;
      col_down = (j + 1) * 8;
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (t = 0; t < 9; t++) {
        if (t == 4) {
          continue;
        }
        if (row_up >= 0 && col_up >= 0) {
          t += orig[row_up * 8 + col_up];
        }
        if (row_up >= 0 && col < 8) {
          t += orig[row_up * 8 + col];
        }
        if (row_up >= 0 && col_down < 8) {
          t += orig[row_up * 8 + col_down];
        }
        if (row < 8 && col_up >= 0) {
          t += orig[row * 8 + col_up];
        }
        if (row < 8 && col < 8) {
          t += orig[row * 8 + col];
        }
        if (row < 8 && col_down < 8) {
          t += orig[row * 8 + col_down];
        }
        if (row_down < 8 && col_up >= 0) {
          t += orig[row_down * 8 + col_up];
        }
        if (row_down < 8 && col < 8) {
          t += orig[row_down * 8 + col];
        }
        if (row_down < 8 && col_down < 8) {
          t += orig[row_down * 8 + col_down];
        }
      }
      sol[row * 8 + col] = t;
    }
  }
}