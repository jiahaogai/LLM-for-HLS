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
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    for (col = 1; col < 8191; col++) {
      t = 0;
      int loop_filter[9];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_loop_filter:
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        loop_loop_col_filter:
        for (j = -4; j < 5; j++) {
          int _in;
          _in = orig[((((row + i)) + 1) * 8192) + (((col + j)) + 1)];
          loop_filter[((i + 4) * 9) + (j + 4)] = _in;
          t += (_in * filter[((i + 4) * 9) + (j + 4)]);
        }
      }
      sol[((row * 8192) + col)] = t;
    }
  }
}