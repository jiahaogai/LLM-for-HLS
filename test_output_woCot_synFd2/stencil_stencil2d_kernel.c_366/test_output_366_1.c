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
  int col_up;
  int col_down;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8 + j;
      row_up = row - 8;
      row_down = row + 8;
      col_up = j - 8;
      col_down = j + 8;
      val = ((row_up < 0) ? 0 : orig[row_up * 8 + col_up]) + ((row_down >= 8 * 8) ? 0 : orig[row_down * 8 + col_up]) + ((col_up < 0) ? 0 : orig[row_up * 8 + col_up]) + ((col_down >= 8 * 8) ? 0 : orig[row_down * 8 + col_down]) - 4 * orig[row * 8 + j];
      sol[row * 8 + j] = val;
    }
  }
}