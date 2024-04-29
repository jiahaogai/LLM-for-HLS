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
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      loopk:
      for (k = 0; k < 8; k++) {
        row_up = (j - 1 - k);
        row_down = (8191 - j + k);
        if (row_up < 1) {
          row_up = 1;
        }
        if (row_down < 1) {
          row_down = 1;
        }
        if (k_col == 4) {
          tmp += orig[row_down] + 2 * orig[j] + orig[row_up];
        }
        else {
          tmp += orig[row_down] + orig[j] + orig[row_up];
        }
      }
      col_up = (k_col - 1);
      col_down = (9 - 1 - k_col);
      if (col_up < 1) {
        col_up = 1;
      }
      if (col_down < 1) {
        col_down = 1;
      }
      sol[j] = ((filter[k_col] * tmp) / (col_down * col_up));
    }
  }
}