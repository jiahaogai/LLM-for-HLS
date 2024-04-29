#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int row;
  int col;
  row = 0;
=======
  int sum;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  loop_row:
  while (row < 80) {
    col = 0;
=======
  outer:
  for (i = 0; i < 8; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    while (col < 80) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row + ((k / 3) - 1);
        j = col + ((k % 3) - 1);
        if (i >= 0 && i < 80 && j >= 0 && j < 80) {
          t += orig[i * 80 + j] * filter[k];
        }
      }
      sol[row * 80 + col] = t;
      col++;
    }
    row++;
=======
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        sum += filter[k] * orig[row * 8 + col];
      }
      sol[i * 8 + j] = sum;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}