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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 8; j < 8192; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = -1; col <= 1; col++) {
          row_up = i + row * 8;
          row_down = i + (row + 1) * 8;
          col_left = j + col * 8;
          col_right = j + (col + 1) * 8;
          t += filter[4 + col * 2 + (row * 2)] * orig[row_up * 8192 + col_left];
          t += filter[4 + col * 2 + (row * 2 + 1)] * orig[row_down * 8192 + col_left];
          t += filter[4 + col * 2 + (row * 2 + 2)] * orig[row_down * 8192 + col_right];
          t += filter[4 + col * 2 + (row * 2 + 3)] * orig[row_up * 8192 + col_right];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}