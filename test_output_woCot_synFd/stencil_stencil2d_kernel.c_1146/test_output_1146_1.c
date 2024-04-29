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
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (row = -1 + i; row < 8 + i; ++row) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = -1 + j; col < 8 + j; ++col) {
          row_up = row - 1;
          row_down = row + 1;
          col_left = col - 1;
          col_right = col + 1;
          if (row_up < 0) {
            row_up = 0;
          }
          if (row_down > 8183) {
            row_down = 8183;
          }
          if (col_left < 0) {
            col_left = 0;
          }
          if (col_right > 8183) {
            col_right = 8183;
          }
          t += filter[0] * orig[row_up * 8192 + col_left];
          t += filter[1] * orig[row_up * 8192 + col];
          t += filter[2] * orig[row_up * 8192 + col_right];
          t += filter[3] * orig[row * 8192 + col_left];
          t += filter[4] * orig[row * 8192 + col];
          t += filter[5] * orig[row * 8192 + col_right];
          t += filter[6] * orig[row_down * 8192 + col_left];
          t += filter[7] * orig[row_down * 8192 + col];
          t += filter[8] * orig[row_down * 8192 + col_right];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}