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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
<<<<<<< HEAD
      row = i * 64;
      row_up = row - 1;
      row_down = row + 1;
      col = j * 8;
      col_left = col - 1;
      col_right = col + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (int k = 0; k < 9; k++) {
        if (k == 4) {
          continue;
        }
        t += filter[k] * orig[row_up * 64 + col_left + k - 4];
      }
      sol[row * 64 + col] = t;
=======
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_left = j * 8 - 1;
      col_right = j * 8 + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (t = 0; t < 9; t++) {
        if ((((0 <= row_up) && (row_up < 8192)) && (0 <= col_left)) && (col_left < 8192)) {
          t += orig[row_up * 8 + col_left];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        if ((((0 <= row_up) && (row_up < 8192)) && (0 <= col)) && (col < 8192)) {
          t += orig[row_up * 8 + col];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        if ((((0 <= row_up) && (row_up < 8192)) && (0 <= col_right)) && (col_right < 8192)) {
          t += orig[row_up * 8 + col_right];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        if ((((0 <= row) && (row < 8192)) && (0 <= col_left)) && (col_left < 8192)) {
          t += orig[row * 8 + col_left];
        }
        
#pragma ACCEL PIPELINE auto{flatten}
        if ((((0 <= row) && (row < 8192)) && (0 <= col)) && (col < 8192)) {
          sol[row * 8 + col] = t;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        if ((((0 <= row) && (row < 8192)) && (0 <= col_right)) && (col_right < 8192)) {
          t += orig[row * 8 + col_right];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        if ((((0 <= row_down) && (row_down < 8192)) && (0 <= col_left)) && (col_left < 8192)) {
          t += orig[row_down * 8 + col_left];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        if ((((0 <= row_down) && (row_down < 8192)) && (0 <= col)) && (col < 8192)) {
          t += orig[row_down * 8 + col];
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        if ((((0 <= row_down) && (row_down < 8192)) && (0 <= col_right)) && (col_right < 8192)) {
          t += orig[row_down * 8 + col_right];
        }
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}