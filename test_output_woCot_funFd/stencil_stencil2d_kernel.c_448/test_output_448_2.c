#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int s;
=======
  int row;
  int col;
  int flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (i + 4 - ((8 + 1 - k) / 2)) * 256 + j + 4 - ((8 + 1 - k) / 2);
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 256 + j] = (int )s;
=======
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 256;
      flit = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        flit += orig[row + filter[k]] * filter[k];
      }
      sol[col + i] = flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}