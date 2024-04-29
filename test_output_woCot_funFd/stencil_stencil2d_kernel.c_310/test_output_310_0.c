#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
<<<<<<< HEAD
  int pt = 4;
=======
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
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      for (pt = 0; pt < 9; pt++) {
        t += filter[pt] * orig[i + (-4 + pt) * 8192 + j];
=======
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8192; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (row = -1 + -8; row <= -1 + 8; row += 1) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = -1 + -8; col <= -1 + 8; col += 1) {
          row_up = i + row;
          row_down = i + 8 + row;
          col_left = j + col;
          col_right = j + 8 + col;
          t += filter[4 + col] * orig[row_up * 8192 + col_left];
          t += filter[1 + col] * orig[row_up * 8192 + col_right];
          t += filter[4 + col] * orig[row_down * 8192 + col_left];
          t += filter[1 + col] * orig[row_down * 8192 + col_right];
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 8192 + j] = t;
    }
  }
}