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
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1; k < 33 - 1; k++) {
      row_up = 33 * (j - 1) + 1;
      row_down = 33 * (j + 1) - 1;
      col_up = 1 * (k - 1);
      col_down = 1 * (k + 1) - 1;
      row = 33 * j + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopt:
      for (t = 0; t < 9; t++) {
        orig[row + col_up] = ((0 * filter[t]) + (1 * orig[row_up + col_up]) + (2 * orig[row_up + col]) + (3 * orig[row_up + col_down]) + (4 * orig[row + col_down]) + (5 * orig[row_down + col_down]) + (6 * orig[row_down + col]) + (7 * orig[row_down + col_up]) + (8 * orig[row + col_up]));
      }
    }
  }
//#pragma endscop
}