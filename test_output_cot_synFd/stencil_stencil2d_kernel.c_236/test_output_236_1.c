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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 64;
      row_up = row - 1;
      row_down = row + 1;
      col = j * 64;
      col_left = col - 1;
      col_right = col + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        if (k == 4) {
          continue;
        }
        t += filter[k] * orig[row_up * 8 + col_left + k - 4];
      }
      sol[row * 8 + col] = t;
    }
  }
}