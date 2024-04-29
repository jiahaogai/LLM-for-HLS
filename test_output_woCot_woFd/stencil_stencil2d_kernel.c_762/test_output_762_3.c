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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_stencil_1:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
  for (i = 0; i <= 7; i++) {
    row = 8 * i;
    loop_stencil_2:
/* Standardize from: for(j = 0; j < 8; j++) {...} */
    for (j = 0; j <= 7; j++) {
      t = 0;
      col = 8 * j;
      loop_stencil_3:
/* Standardize from: for(k = -4; k < 5; k++) {...} */
      for (k = -4; k <= 3; k++) {
        row_up = row + ((k > 3) ? 8 : 0);
        row_down = row + ((k < -3) ? 8 : 0);
        loop_stencil_4:
/* Standardize from: for(l = -4; l < 5; l++) {...} */
        for (l = -4; l <= 3; l++) {
          col_left = col + ((l > 3) ? 8 : 0);
          col_right = col + ((l < -3) ? 8 : 0);
          t += filter[k + 4] * filter[l + 4] * orig[col_right + row_down];
        }
      }
      sol[col + row] = t;
    }
  }
}