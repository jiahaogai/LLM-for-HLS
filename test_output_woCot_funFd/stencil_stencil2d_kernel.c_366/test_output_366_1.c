#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int val;
=======
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8 + j;
      row_up = row - 8;
      row_down = row + 8;
      col_up = j - 8;
      col_down = j + 8;
      val = ((row_up < 0) ? 0 : orig[row_up * 8 + col_up]) + ((row_down >= 8 * 8) ? 0 : orig[row_down * 8 + col_up]) + ((col_up < 0) ? 0 : orig[row_up * 8 + col_up]) + ((col_down >= 8 * 8) ? 0 : orig[row_down * 8 + col_down]) - 4 * orig[row * 8 + j];
      sol[row * 8 + j] = val;
=======
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8188; j++) {
      result = ((0 + filter[0]) * orig[i * 8192 + j]) + ((0 + filter[1]) * orig[i * 8192 + j + 1]) + ((0 + filter[2]) * orig[i * 8192 + j + 2]) + ((0 + filter[3]) * orig[i * 8192 + j + 3]) + ((0 + filter[4]) * orig[i * 8192 + j + 4]) + ((0 + filter[5]) * orig[i * 8192 + j + 5]) + ((0 + filter[6]) * orig[i * 8192 + j + 6]) + ((0 + filter[7]) * orig[i * 8192 + j + 7]) + ((0 + filter[8]) * orig[i * 8192 + j + 8]);
      sol[i * 8192 + j] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8188; j++) {
      orig[i * 8192 + j] = sol[i * 8192 + j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}