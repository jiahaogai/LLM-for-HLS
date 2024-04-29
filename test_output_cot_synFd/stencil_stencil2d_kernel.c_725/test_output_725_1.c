#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int fl;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      fl = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (row = i - 1; row <= i + 1; row++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (col = j - 1; col <= j + 1; col++) {
          if (row == i && col == j) {
            continue;
          }
          fl += orig[row][col] * filter[row - i + 1 + 1][col - j + 1 + 1];
        }
      }
      sol[i][j] = fl;
    }
  }
}