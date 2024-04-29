#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  int tmp;
  int offset;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8192; j += 8) {
      offset = i * 8192 + j;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; ++k) {
        row_up = i - 1;
        row_down = i + 1;
        if (row_up == -1) {
          row_up = 0;
        }
        if (row_down == 8192) {
          row_down = 8191;
        }
        col_left = j - 1;
        col_right = j + 1;
        if (col_left == -1) {
          col_left = 0;
        }
        if (col_right == 8192) {
          col_right = 8191;
        }
        row = row_up * 8192 + col_left;
        tmp += filter[k] * orig[row];
        row = row_up * 8192 + col_right;
        tmp += filter[k] * orig[row];
        row = row_down * 8192 + col_left;
        tmp += filter[k] * orig[row];
        row = row_down * 8192 + col_right;
        tmp += filter[k] * orig[row];
      }
      sol[offset] = tmp;
    }
  }
}