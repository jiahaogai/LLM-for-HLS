#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 256;
      sol_row = i * 256;
      orig_col = j;
      sol_col = j;
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int k_col = k % 3;
        int i_col = i + (-1 + k_col);
        int j_col = j + (-1 + (k - k_col));
        if (i_col >= 0 && i_col < 256 && j_col >= 0 && j_col < 256) {
          sum += orig[i_col * 256 + j_col] * filter[k];
        }
      }
      sol[sol_row + sol_col] = sum;
=======
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) << 8)] - filter[k]) << 8 | j + (-4 + k);
        val += orig[idx] * filter[k];
      }
      sol[i << 8 | j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}