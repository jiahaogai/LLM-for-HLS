#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int sum;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4];
      }
      sol[j] = result;
=======
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        if (((row >= 0) && (row < 256)) && ((col >= 0) && (col < 256))) {
          sum += orig[row * 256 + col] * filter[k];
        }
      }
      sol[i * 256 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}