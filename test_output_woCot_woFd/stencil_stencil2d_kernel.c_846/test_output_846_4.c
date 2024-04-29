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
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (row = -1 + -8; row <= 8 + -8; row += 1) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = -1 + -8; col <= 8 + -8; col += 1) {
          row_up = i + row;
          row_down = i + 8 + row;
          col_left = j + col;
          col_right = j + 8 + col;
          t += filter[col + 8] * orig[row_up * 8192 + col_left];
          t += filter[col + 7] * orig[row_up * 8192 + col_right];
          t += filter[col + 8] * orig[row_down * 8192 + col_left];
          t += filter[col + 7] * orig[row_down * 8192 + col_right];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}