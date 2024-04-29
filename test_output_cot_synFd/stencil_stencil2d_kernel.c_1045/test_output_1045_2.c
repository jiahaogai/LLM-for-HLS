#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      row_up = (i == 0 ? 0 : i - 1);
      row_down = (i == 255 ? 255 : i + 1);
      col_up = (j == 0 ? 0 : j - 1);
      col_down = (j == 255 ? 255 : j + 1);
      val = orig[i * 256 + j] + filter[0] * orig[row_up * 256 + col_up] + filter[1] * orig[row_up * 256 + j] + filter[2] * orig[row_up * 256 + col_down] + filter[3] * orig[row * 256 + col_down] + filter[4] * orig[row_down * 256 + col_down] + filter[5] * orig[row_down * 256 + j] + filter[6] * orig[row_down * 256 + col_up];
      sol[i * 256 + j] = val;
    }
  }
}