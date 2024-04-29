#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (column = 1; column < 400 - 1; column++) {
      value = 0;
      int fi = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      while (fi < 25) {
        i = row - 1 + fi / 5;
        j = column - 1 + fi % 5;
        value += orig[i][j] * filter[fi];
        fi++;
      }
      sol[row][column] = value;
    }
  }
}