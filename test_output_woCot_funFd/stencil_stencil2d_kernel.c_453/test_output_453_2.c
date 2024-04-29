#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
=======
  int idx;
  int idy;
  int s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
<<<<<<< HEAD
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
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + ((k + 1) % 9) - 1;
        idy = j + ((k + 1) / 9) - 1;
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 255) {
          idx = 255;
        }
        if (idy < 0) {
          idy = 0;
        }
        if (idy > 255) {
          idy = 255;
        }
        s += filter[k] * orig[idx * 256 + idy];
      }
      sol[i * 256 + j] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}