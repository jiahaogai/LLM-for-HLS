#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
=======
  int row;
  int col;
  int flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8192; j += 8) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + k - 4 + ((j + k - 4) % 8192)];
      }
      sol[i + j - 8] = sum;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 256;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        flit += filter[k] * orig[row + flit_row[k]] * orig[col + flit_col[k]];
      }
      sol[row + col] = flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}