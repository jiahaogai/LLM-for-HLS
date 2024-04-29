#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int t;
  int pt = 4;
=======
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    t = 0;
=======
  for (i = 0; i < 8; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + (j - 4)];
    }
    sol[i] = t;
=======
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_left = j * 8 - 1;
      col_right = j * 8 + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (int k = 0; k < 9; ++k) {
        if (((0 <= row_up) && (row_up < 8192)) && ((0 <= col_left) && (col_left < 8192))) {
          t += filter[k] * orig[row_up * 8 + col_left];
        }
        
        if (((0 <= row_up) && (row_up < 8192)) && ((0 <= col) && (col < 8192))) {
          t += filter[k] * orig[row_up * 8 + col];
        }
        
        if (((0 <= row_up) && (row_up < 8192)) && ((0 <= col_right) && (col_right < 8192))) {
          t += filter[k] * orig[row_up * 8 + col_right];
        }
        
        if (((0 <= row) && (row < 8192)) && ((0 <= col_left) && (col_left < 8192))) {
          t += filter[k] * orig[row * 8 + col_left];
        }
        
        if (((0 <= row) && (row < 8192)) && ((0 <= col_right) && (col_right < 8192))) {
          t += filter[k] * orig[row * 8 + col_right];
        }
        
        if (((0 <= row_down) && (row_down < 8192)) && ((0 <= col_left) && (col_left < 8192))) {
          t += filter[k] * orig[row_down * 8 + col_left];
        }
        
        if (((0 <= row_down) && (row_down < 8192)) && ((0 <= col) && (col < 8192))) {
          t += filter[k] * orig[row_down * 8 + col];
        }
        
        if (((0 <= row_down) && (row_down < 8192)) && ((0 <= col_right) && (col_right < 8192))) {
          t += filter[k] * orig[row_down * 8 + col_right];
        }
      }
      sol[row * 8 + col] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}