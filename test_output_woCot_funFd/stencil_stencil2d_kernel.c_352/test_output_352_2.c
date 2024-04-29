#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int e;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (column = 1; column < 400 - 1; column++) {
      e = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner_e:
      for (i = -1; i <= 1; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        inner_i:
        for (j = -1; j <= 1; j++) {
          e += filter[((i + 1) * 3) + (j + 1)] * orig[row + i][column + j];
        }
      }
      sol[row][column] = e;
    }
  }
}