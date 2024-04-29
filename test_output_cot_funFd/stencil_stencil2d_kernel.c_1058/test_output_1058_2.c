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
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    int tmp = filter[4] * orig[i];
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner1:
    for (j = 1; j < 8; j++) {
      tmp += filter[j] * (orig[i + j] + orig[i - j]);
    }
    sol[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer1:
  for (i = 0; i < 8192; i++) {
    int tmp = filter[4] * sol[i];
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner2:
    for (j = 1; j < 8; j++) {
      tmp += filter[j] * (sol[i + j] + sol[i - j]);
    }
    t = tmp / filter[4];
    row = i % 64;
    row_up = (i - 1) % 64;
    row_down = (i + 1) % 64;
    col_left = row - 1;
    col_right = row + 1;
    if (col_left < 0) {
      col_left = 0;
    }
    if (col_right > 63) {
      col_right = 63;
    }
    if (tmp >= sol[i]) {
      col = 64 + (-1 * tmp) / (sol[i] - tmp);
    }
    else {
      col = 1 + t / (sol[i] - tmp);
    }
    if (col_left == col) {
      sol[row_up * 64 + col_left] = ((sol[row_up * 64 + col_left]) * 4 + orig[row * 64 + col_left]) / 5;
    }
    else if (col_right == col) {
      sol[row_up * 64 + col_right] = ((sol[row_up * 64 + col_right]) * 4 + orig[row * 64 + col_right]) / 5;
    }
    else {
      sol[row_up * 64 + col] = ((sol[row_up * 64 + col]) * 1 + orig[row * 64 + col] * 4) / 5;
    }
    if (col_left == col) {
      sol[row_down * 64 + col_left] = ((sol[row_down * 64 + col_left]) * 1 + orig[row * 64 + col_left] * 4) / 5;
    }
    else if (col_right == col) {
      sol[row_down * 64 + col_right] = ((sol[row_down * 64 + col_right]) * 1 + orig[row * 64 + col_right] * 4) / 5;
    }
    else {
      sol[row_down * 64 + col] = ((sol[row_down * 64 + col]) * 4 + orig[row * 64 + col] * 1) / 5;
    }
  }
}