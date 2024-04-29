#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int e;
  int v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (column = 1; column < 400 - 1; column++) {
      v = 0;
      e = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = -12; i <= 12; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = -12; j <= 12; j++) {
          e += filter[25 - ((i * 12) + j)] * orig[row + i][column + j];
          v++;
        }
      }
      sol[row][column] = e / v;
    }
  }
}