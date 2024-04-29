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
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 1; k_col < 33; k_col++) {
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        row_up = j - 1 + k - 4;
        row_down = j - 1 + k - 3;
        if (row_up < 1) {
          row_up = 1;
        }
        if (row_down > 32) {
          row_down = 32;
        }
        loopi:
        for (i = 1; i < 33; i++) {
          col_up = i - 1 + k - 4;
          col_down = i - 1 + k - 3;
          if (col_up < 1) {
            col_up = 1;
          }
          if (col_down > 32) {
            col_down = 32;
          }
          t += ((orig[row_down * 32 + col_down] - orig[row_up * 32 + col_up]) / 4) * filter[k];
        }
      }
      sol[j * 32 + k_col] = t;
    }
  }
}