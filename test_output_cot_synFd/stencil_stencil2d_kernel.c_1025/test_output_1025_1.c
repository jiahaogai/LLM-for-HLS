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
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loop:
  for (i = 0; i < 8192; i++) {
    row = i & 127;
    row_up = (row - 1 + 128) % 128;
    row_down = (row + 1) % 128;
    col = i >> 7;
    col_up = col;
    col_down = col;
    t = 0;
    loop_up:
    for (j = 0; j < 8; j++) {
      t += orig[row_up * 128 + col_up] * filter[j];
      col_up = (col_up - 1) % 128;
    }
    sol[i] = t;
    loop_down:
    for (j = 0; j < 8; j++) {
      t += orig[row_down * 128 + col_down] * filter[j];
      col_down = (col_down + 1) % 128;
    }
  }
}