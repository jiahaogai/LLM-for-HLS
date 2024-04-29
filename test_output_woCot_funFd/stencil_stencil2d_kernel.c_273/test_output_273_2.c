#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 8 + j + ((k - 4) * 8)];
      }
      sol[i * 8 + j] = result;
=======
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_row_up:
    for (row_up = row - 1; row_up > 0; row_up--) {
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{16}
      loop_col_up:
      for (col_up = 1; col_up < 81; col_up++) {
        flit += filter[0] * orig[row_up * 81 + col_up - 1];
        flit += filter[1] * orig[row_up * 81 + col_up];
        flit += filter[2] * orig[row_up * 81 + col_up + 1];
        flit += filter[3] * orig[row_up * 81 + col_up + 80];
        flit += filter[4] * orig[row_up * 81 + col_up + 81];
        flit += filter[5] * orig[row_up * 81 + col_up + 82];
      }
      sol[row_up * 81] = flit;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 81; col++) {
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{1}
      loop_row_up_1:
      for (row_up = row - 1; row_up > 0; row_up--) {
        flit += filter[0] * orig[row_up * 81 + col - 1];
      }
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{1}
      loop_row_down:
      for (row_down = row + 1; row_down < 8192; row_down++) {
        flit += filter[5] * orig[row_down * 81 + col + 82];
        flit += filter[4] * orig[row_down * 81 + col + 81];
        flit += filter[3] * orig[row_down * 81 + col + 80];
        flit += filter[2] * orig[row_down * 81 + col + 1];
        flit += filter[1] * orig[row_down * 81 + col];
        flit += filter[0] * orig[row_down * 81 + col - 1];
      }
      sol[row * 81 + col] = flit;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_row_down_1:
    for (row_down = row + 1; row_down < 8192; row_down++) {
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{16}
      loop_col_down:
      for (col_down = 1; col_down < 81; col_down++) {
        flit += filter[0] * orig[row_down * 81 + col_down - 1];
        flit += filter[1] * orig[row_down * 81 + col_down];
        flit += filter[2] * orig[row_down * 81 + col_down + 1];
        flit += filter[3] * orig[row_down * 81 + col_down + 80];
        flit += filter[4] * orig[row_down * 81 + col_down + 81];
        flit += filter[5] * orig[row_down * 81 + col_down + 82];
      }
      sol[row_down * 81] = flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}