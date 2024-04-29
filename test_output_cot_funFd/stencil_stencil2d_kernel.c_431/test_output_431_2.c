#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 64) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        int orig_row = row + k;
        int orig_col = col - 4;
        int filter_index = (k + 4) << 4;
        t += orig[orig_row * 64 + orig_col] * filter[filter_index + 4];
        for (int m = 0; m < 8; m++) {
          t += orig[orig_row * 64 + orig_col + m] * filter[filter_index + m];
        }
      }
      sol[row * 64 + col] = t;
      col++;
    }
    row++;
  }
}