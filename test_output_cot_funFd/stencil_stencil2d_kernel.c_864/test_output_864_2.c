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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_up:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    loop_down:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      int filter_elem;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_filter:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        row_up = i - 4 + filter_elem;
        row_down = i + 3 - filter_elem;
        row = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_up_row:
        for (; row < 8; row++) {
          if (row_up < 0) {
            row_up += 8192;
          }
          if (row_down >= 8192) {
            row_down -= 8192;
          }
          col = 0;
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          loop_col:
          for (; col < 8; col++) {
            int orig_elem;
            int sol_elem;
            orig_elem = orig[row_up + col];
            sol_elem = sol[row_up + col];
            t += orig_elem * filter[filter_elem];
            sol[row_down + col] = sol_elem + t;
          }
        }
      }
    }
  }
}