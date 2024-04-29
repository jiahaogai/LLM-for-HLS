#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      row_up = (i - 1 + 256) % 256;
      row_down = (i + 1) % 256;
      col_left = (j - 1 + 256) % 256;
      col_right = (j + 1) % 256;
      tmp = orig[i * 256 + j] + filter[0] * orig[row_up * 256 + col_left] + filter[1] * orig[row_up * 256 + j] + filter[2] * orig[row_up * 256 + col_right] + filter[3] * orig[row * 256 + col_left] + filter[4] * orig[row * 256 + j] + filter[5] * orig[row * 256 + col_right] + filter[6] * orig[row_down * 256 + col_left] + filter[7] * orig[row_down * 256 + j] + filter[8] * orig[row_down * 256 + col_right];
      sol[i * 256 + j] = tmp;
    }
  }
}