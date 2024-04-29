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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8192; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; ++k) {
        row_up = i - 1;
        row_down = i + 1;
        col_left = j - 1;
        col_right = j + 1;
        if (row_up == -1) {
          row_up = 0;
        }
        if (col_left == -1) {
          col_left = 0;
        }
        if (row_down == 8192) {
          row_down = 8184;
        }
        if (col_right == 8192) {
          col_right = 8184;
        }
        t += orig[row_up * 8192 + col_left] * filter[k];
        t += orig[row_up * 8192 + j] * filter[k];
        t += orig[row_up * 8192 + col_right] * filter[k];
        t += orig[i * 8192 + col_left] * filter[k];
        t += orig[i * 8192 + col_right] * filter[k];
        t += orig[row_down * 8192 + col_left] * filter[k];
        t += orig[row_down * 8192 + j] * filter[k];
        t += orig[row_down * 8192 + col_right] * filter[k];
      }
      sol[i * 8192 + j] = t;
    }
  }
}