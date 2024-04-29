#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
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
    }
  }
}