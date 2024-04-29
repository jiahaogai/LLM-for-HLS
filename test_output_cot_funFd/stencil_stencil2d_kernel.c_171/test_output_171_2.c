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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
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
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (t = 0; t < 9; t++) {
        if (t != 4) {
          if ((((8192 > row_up) && (row_up >= 0)) && ((8192 > col_up) && (col_up >= 0))) && filter[t]) {
            t += orig[row_up * 64 + col_up];
          }
          if ((((8192 > row_up) && (row_up >= 0)) && ((8192 > col) && (col >= 0))) && filter[t]) {
            t += orig[row_up * 64 + col];
          }
          if ((((8192 > row_up) && (row_up >= 0)) && ((8192 > col_down) && (col_down >= 0))) && filter[t]) {
            t += orig[row_up * 64 + col_down];
          }
          if ((((8192 > row) && (row >= 0)) && ((8192 > col_up) && (col_up >= 0))) && filter[t]) {
            t += orig[row * 64 + col_up];
          }
          if ((((8192 > row) && (row >= 0)) && ((8192 > col_down) && (col_down >= 0))) && filter[t]) {
            t += orig[row * 64 + col_down];
          }
          if ((((8192 > row_down) && (row_down >= 0)) && ((8192 > col_up) && (col_up >= 0))) && filter[t]) {
            t += orig[row_down * 64 + col_up];
          }
          if ((((8192 > row_down) && (row_down >= 0)) && ((8192 > col) && (col >= 0))) && filter[t]) {
            t += orig[row_down * 64 + col];
          }
          if ((((8192 > row_down) && (row_down >= 0)) && ((8192 > col_down) && (col_down >= 0))) && filter[t]) {
            t += orig[row_down * 64 + col_down];
          }
        }
      }
      sol[row * 64 + col] = t;
    }
  }
}