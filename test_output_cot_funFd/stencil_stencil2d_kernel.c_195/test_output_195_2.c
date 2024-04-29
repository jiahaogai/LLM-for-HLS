#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int bottom_pad;
  int side_pad;
  int top_pad;
  int pad;
  int row_up;
  int row;
  int row_down;
  int col_left;
  int col;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad = 1;
  bottom_pad = 8;
  side_pad = 8;
  top_pad = 8;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row_up = 1 + top_pad;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  row = 1 + pad + top_pad;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row_down = 8191 - bottom_pad;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  col_left = 1 + side_pad;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  col = 1 + pad + side_pad;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  col_right = 8191 - side_pad;
/* Standardize from here. */
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 8192; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        int cur_x = i - bottom_pad + row_up + k;
        int cur_y = j - side_pad + col_left + k;
        if (cur_x >= 0 && cur_x < 8192 && cur_y >= 0 && cur_y < 8192) {
          index = cur_x * 8192 + cur_y;
          sum += orig[index] * filter[k];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}