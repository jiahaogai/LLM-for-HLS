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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loop_up:
/* Standardize from: for(row = 1; row < 8191; row++) {...} */
  for (row = 1 + 8191 * 0; row < 8191 + 8191 * 1; row += 8191 * 1) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_left:
    for (col = 1; col < 8192; col++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      loop_z:
      for (k = 0; k < 9; k++) {
        i = row + (-1 + k);
        t += orig[i * 8192 + col] * filter[k];
      }
      sol[row * 8192 + col] = t;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_right:
    for (col = 8190; col >= 1; col--) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_x:
      for (k = 0; k < 9; k++) {
        j = col + (-1 + k);
        t += orig[row * 8192 + j] * filter[k];
      }
      sol[row * 8192 + col] = t;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_down:
/* Standardize from: for(row = 8190; row > 1; row--) {...} */
  for (row = 8190 + -1 + 0; row > 1 + -1 + 0; row += -1 + 0) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_left_1:
    for (col = 1; col < 8192; col++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_y:
      for (k = 0; k < 9; k++) {
        j = col + (-1 + k);
        t += orig[j * 8192 + row] * filter[k];
      }
      sol[row * 8192 + col] = t;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_right_1:
    for (col = 8190; col >= 1; col--) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loop_y_1:
      for (k = 0; k < 9; k++) {
        j = col + (-1 + k);
        t += orig[j * 8192 + row] * filter[k];
      }
      sol[row * 8192 + col] = t;
    }
  }
}