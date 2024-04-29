#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int row;
  int column;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 4; j++) {
      tmp = 0;
      inner_filter:
      for (fl = 0; fl < 2; fl++) {
        inner_row:
        for (row = i - 1; row <= i + 1; row++) {
          inner_column:
          for (column = j - 1; column <= j + 1; column++) {
            if (row == i && column == j) {
              continue;
            }
            if (row < 0 || row > 3 || column < 0 || column > 3) {
              tmp += orig[i][j] * filter[fl][0];
            }
            else {
              tmp += orig[row][column] * filter[fl][1];
            }
          }
        }
      }
      sol[i][j] = tmp;
    }
  }
}