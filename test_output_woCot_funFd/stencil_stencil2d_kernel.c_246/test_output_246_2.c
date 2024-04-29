Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_stencil_1:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_stencil_2:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_up = (j - 1) * 8;
      col_down = (j + 1) * 8;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_stencil_3:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[row + (_off_up_down[k] + 0)[row_up,row,row_down] + (_off_left_right[k] + 0)[col_up,col,col_down]];
      }
      sol[row + col] = t;
    }
  }
}