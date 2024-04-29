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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 8191; col++) {
      t = 0;
      row_up = row - 1;
      row_down = row + 1;
      col_left = col - 1;
      col_right = col + 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loop_t:
      for (t = 0; t < 9; t++) {
        if (row_up > 0 && col_left > 0) {
          t += filter[t] * orig[row_up - 1][col_left - 1];
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (row_up > 0) {
          t += filter[t] * orig[row_up - 1][col - 1];
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (row_up > 0 && col_right < 8191) {
          t += filter[t] * orig[row_up - 1][col_right];
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (col_left > 0) {
          t += filter[t] * orig[row - 1][col_left - 1];
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_t_2:
        for (t = 0; t < 9; t++) {
          if (row_down < 8191 && col_left > 0) {
            t += filter[t] * orig[row_down][col_left - 1];
          }
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (row_down < 8191) {
          t += filter[t] * orig[row_down][col - 1];
        }
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_t_3:
        for (t = 0; t < 9; t++) {
          if (row_down < 8191 && col_right < 8191) {
            t += filter[t] * orig[row_down][col_right