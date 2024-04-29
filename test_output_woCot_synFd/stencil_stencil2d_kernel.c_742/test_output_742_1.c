#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 32; j-- > 32; ) {
    row = 8 * j;
    row_up = 8 * (j - 1);
    row_down = 8 * (j + 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 32; k-- > 32; ) {
      col = 8 * k;
      col_up = 8 * (k - 1);
      col_down = 8 * (k + 1);
      t = filter[0] * orig[row_up + col_up] + filter[1] * orig[row_up + col] + filter[2] * orig[row_up + col_down] + filter[3] * orig[row + col_down] + filter[4] * orig[row_down + col_down] + filter[5] * orig[row_down + col] + filter[6] * orig[row_down + col_up] + filter[7] * orig[row + col_up];
      sol[row + col] = t;
    }
  }
}