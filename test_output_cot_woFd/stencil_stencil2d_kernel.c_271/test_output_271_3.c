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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int filter_elem = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        int index = filter_elem + (i - 4);
        int index_up = index + 1;
        int index_down = index - 1;
        int index_left = filter_elem - 4;
        int index_right = 8 - filter_elem;
        if (index >= 0 && index < 256) {
          if (index_up >= 0 && index_up < 256) {
            row_up = index_up * 256 + j;
            t += orig[row_up] * filter[index_up];
          }
          if (index_down >= 0 && index_down < 256) {
            row_down = index_down * 256 + j;
            t += orig[row_down] * filter[index_down];
          }
        }
        if (index_left >= 0 && index_left < 256) {
          col_left = i - 4 + index_left;
          t += orig[col_left * 256 + j] * filter[index_left];
        }
        if (index_right >= 0 && index_right < 256) {
          col_right = i - 4 + index_right;
          t += orig[col_right * 256 + j] * filter[index_right];
        }
      }
      row = i * 256 + j;
      sol[row] = t;
    }
  }
}