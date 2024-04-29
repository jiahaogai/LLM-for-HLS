#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_row;
  int i_row_up;
  int i_row_down;
  int i_col;
  int i_col_left;
  int i_col_right;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row_up:
/* Standardize from: for(i_row = 1; i_row < 8192 - 1; i_row++) {...} */
  for (i_row = 1; i_row <= 8192 - 1; i_row++) {
     i_row_up = 8192 + i_row - 1;
     i_row_down = i_row_up - 2;
     loop_col_left:
/* Standardize from: for(i_col = 1; i_col < 8192 - 1; i_col++) {...} */
    for (i_col = 1; i_col <= 8192 - 1; i_col++) {
      i_col_left = i_col - 1;
      i_col_right = i_col_left + 1;
      t = ((filter[4] * orig[i_row_down + i_col_left]) + (filter[2] * orig[i_row_down + i_col]) + (filter[1] * orig[i_row_down + i_col_right]) + (filter[8] * orig[i_row_up + i_col_left]) + (filter[5] * orig[i_row_up + i_col]) + (filter[6] * orig[i_row_up + i_col_right]) + (filter[7] * orig[i_row + i_col_left]) + (filter[0] * orig[i_row + i_col]) + (filter[3] * orig[i_row + i_col_right])) / 81;
      sol[i_row - 1 + (i_col - 1) * 8] = t;
    }
  }
}