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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row_up:
  for (row_up = 255; row_up >= 0; row_up--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_row:
    for (row = row_up + 1; row < 256; row++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_col:
      for (col = 1; col < 256; col++) {
        t = 0;
        loop_ignore:
        for (j = -4; j <= 4; j++) {
          loop_ignore:
          for (i = -4; i <= 4; i++) {
            t += filter[4 + i] * orig[row_up * 256 + ((col + i) > 255 ? 255 : (col + i))];
          }
        }
        sol[row * 256 + col] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row_down:
  for (row_down = 1; row_down < 256; row_down++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_row:
    for (row = row_down; row < 257; row++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_col:
      for (col = 1; col < 256; col++) {
        t = 0;
        loop_ignore:
        for (j = -4; j <= 4; j++) {
          loop_ignore:
          for (i = -4; i <= 4; i++) {
            t += filter[4 + i] * orig[((row + j) > 255 ? 255 : (row + j)) * 256 + ((col + i) > 255 ? 255 : (col + i))];
          }
        }
        sol[row * 256 + col] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_col_left:
  for (col_left = 255; col_left >= 0; col_left--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_row: