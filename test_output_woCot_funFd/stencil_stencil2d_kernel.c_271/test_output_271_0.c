#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int idx;
  int val;
=======
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 8; i < 8184; i += 8) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      val = 0;
      filter:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        val += orig[idx] * filter[k];
      }
      sol[i * 256 + j] = val;
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8192; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        inner_1:
        for (col = -1; col <= 1; col++) {
          row_up = i + row * 8;
          row_down = i + (row + 1) * 8;
          col_left = j + col * 8;
          col_right = j + (col + 1) * 8;
          t += orig[row_down][col_right] + orig[row_down][col_left] + orig[row_up][col_right] + orig[row_up][col_left] - orig[row_down][col] - orig[row_up][col] - orig[row][col_right] - orig[row][col_left];
        }
      }
      sol[i / 8][j / 8] = t / 256;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}