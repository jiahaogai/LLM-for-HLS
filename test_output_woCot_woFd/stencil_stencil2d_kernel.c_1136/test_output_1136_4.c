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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int filter_elem:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{4}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner:
        for (col = -1; col <= 1; col++) {
          row_up = (i + row + 256) % 256;
          row_down = (i + row) % 256;
          col_left = (j + col + 256) % 256;
          col_right = (j + col) % 256;
          t += filter[row * 3 + col] * orig[row_up * 256 + col_left];
          t += filter[row * 3 + col] * orig[row_up * 256 + col_right];
          t += filter[row * 3 + col] * orig[row_down * 256 + col_left];
          t += filter[row * 3 + col] * orig[row_down * 256 + col_right];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}