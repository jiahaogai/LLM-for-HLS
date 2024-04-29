#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
=======
void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (column = 1; column < 400 - 1; column++) {
      t = 0;
      inner_1:
      for (i = -1; i <= 1; i++) {
        inner_2:
        for (j = -1; j <= 1; j++) {
          t += orig[row + i][column + j] * filter[25 - ((i >= 0 ? 1 : 0) + (j >= 0 ? 1 : 0))];
        }
      }
      sol[row][column] = t;
=======
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 39; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + (-1 + k);
        idy = j + (-1 + k);
        t += orig[idx][idy] * filter[k];
      }
      sol[i][j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}