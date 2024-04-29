#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
<<<<<<< HEAD
  int pad;
  pad = 1;
=======
  int row;
  int col;
  int flatten_row;
  int flatten_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
=======
  outer:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      t = 0;
      int idx = (((pad - 1) + (i * 8)) * 8) + (pad - 1) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int filter_i = 0; filter_i < 3; filter_i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int filter_j = 0; filter_j < 3; filter_j++) {
          int filter_idx = (filter_i * 3) + filter_j;
          t += orig[idx + (filter_idx - 1)] * filter[filter_idx];
        }
      }
      sol[idx] = t;
=======
    middle:
    for (j = 0; j < 8; j++) {
      row = i - 4 + 0;
      col = j - 4 + 0;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (flatten_row = 0; flatten_row < 5; flatten_row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (flatten_col = 0; flatten_col < 5; flatten_col++) {
          int orig_idx = (row + flatten_row) * 8 + col + flatten_col;
          t += filter[flatten_row * 5 + flatten_col] * orig[orig_idx];
        }
      }
      sol[i * 8 + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}