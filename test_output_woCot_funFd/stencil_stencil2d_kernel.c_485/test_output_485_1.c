#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int row;
  int col;
  int flen;
=======
  int k;
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 8191; j++) {
    loopi:
/* Standardize from: for(i ... ) */
    for (i = 1; i < 8191; i++) {
      t = 0;
      row = j - 4;
      col = i - 4;
/* Standardize from: for(int k = ...> */
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (int k = 0; k < 9; k++) {
        int _row = row + k / 8192;
        int _col = col + k % 8192;
        t += filter[k] * orig[_row * 8192 + _col];
      }
      sol[j * 8192 + i] = t;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 8 + j + ((k - 4) * 8)];
      }
      sol[i * 8 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}