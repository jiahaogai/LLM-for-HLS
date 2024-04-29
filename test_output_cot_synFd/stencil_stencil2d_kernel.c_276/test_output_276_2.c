#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (column = 1; column < 400 - 1; column++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{off}
      inner:
      for (i = -1; i <= 1; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        j_col:
        for (j = -1; j <= 1; j++) {
          t += filter[((i + 1) * 3) + (j + 1)] * orig[row + i][column + j];
        }
      }
      sol[row][column] = t;
    }
  }
}