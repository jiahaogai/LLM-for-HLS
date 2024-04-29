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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int filter_elem;
      
#pragma ACCEL PIPELINE auto{flatten}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        row_up = i - 1 + filter_elem - 4;
        row_down = i + filter_elem - 4;
        col_left = j - 1 + filter_elem - 4;
        col_right = j + filter_elem - 4;
        if (row_up < 0) {
          row_up = 0;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (row_down >= 256) {
          row_down = 255;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        if (col_left < 0) {
          col_left = 0;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        if (col_right >= 256) {
          col_right = 255;
        }
        t += filter[filter_elem] * orig[row_up * 256 + col_left];
        t += filter[filter_elem] * orig[row_up * 256 + col_right];
        t += filter[filter_elem] * orig[row_down * 256 + col_left];
        t += filter[filter_elem] * orig[row_down * 256 + col_right];
      }
      sol[i * 256 + j] = t;
    }
  }
}