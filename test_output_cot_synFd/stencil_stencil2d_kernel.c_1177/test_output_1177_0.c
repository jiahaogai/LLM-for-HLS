#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      t = 0;
      row_up = 8192 + i - 1;
      row_down = i - 1;
      col_up = 8192 + j - 1;
      col_down = j - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loopk:
      for (k = 0; k < 9; k++) {
        row = (k / 3) * 64 + row_up;
        col = (k % 3) * 64 + col_up;
        if (row_up >= 0 && row_up < 8192 && col_up >= 0 && col_up < 8192) {
          t += filter[k] * orig[row_up * 8192 + col_up];
        }
        row = (k / 3) * 64 + row_down;
        col = (k % 3) * 64 + col_down;
        if (row_down >= 0 && row_down < 8192 && col_down >= 0 && col_down < 8192) {
          t += filter[k] * orig[row_down * 8192 + col_down];
        }
      }
      sol[j * 8192 + i] = t;
    }
  }
}