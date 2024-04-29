#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[16])
{
  int row;
  int column;
  int i;
  int j;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (column = 1; column < 400 - 1; column++) {
      t = 0;
      i = row - 1;
      j = column - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      while (i <= row + 1) {
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        while (j <= column + 1) {
          t += orig[i][j] * filter[(((column > 16 ? 16 : column) - 1) + ((column < 400 - 17 ? 17 : 400 - 1) - 1) * 16) / 1];
          j++;
        }
        j = column - 1;
        i++;
      }
      sol[row][column] = t;
    }
  }
}