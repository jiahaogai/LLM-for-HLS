#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
<<<<<<< HEAD
  int k_row;
  int idx;
  int s;
=======
  int i_col;
  int j_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k % 3));
        k_row = ((8 * j) + (k / 3));
        idx = (k_row * 256) + k_col;
        s += ((double )filter[k]) * ((double )orig[idx]);
      }
      sol[((256 * i) + j)] = (int )s;
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 1;
      j_col = j - 1;
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (i_col == -1) i_col = 0;
        if (j_col == -1) j_col = 0;
        if (i_col == 256) i_col = 255;
        if (j_col == 256) j_col = 255;
        sol[i * 256 + j] += orig[i_col * 256 + j_col] * filter[k * 9 + k_col++];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}