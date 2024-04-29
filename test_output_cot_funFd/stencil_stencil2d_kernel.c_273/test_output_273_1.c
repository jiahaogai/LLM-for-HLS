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
  loop_row:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_col:
    for (j = 1; j < 8191; j++) {
      t = 0;
      row_up = (i - 1) * 8192;
      row_down = (i + 1) * 8192;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_up:
      for (col = j - 1; col < 8191; col++) {
        t += orig[col + row_up] * filter[0];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      loop_col_down:
      for (col = j + 1; col < 8192; col++) {
        t += orig[col + row_down] * filter[8];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_col_middle:
      for (col = j; col < 8191; col++) {
        t += orig[col + row_down] * filter[4];
        t += orig[col + row_up] * filter[5];
        t += orig[col + row] * filter[1];
        t += orig[col + row] * filter[2];
        t += orig[col + row] * filter[3];
      }
      sol[j + row] = t;
    }
  }
}