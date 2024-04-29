#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 8192; j++) {
      t = 0;
      row:
      for (row = i - 4; row <= i + 4; row++) {
        col:
        for (j = j - 4; j <= j + 4; j++) {
          t += orig[row * 8192 + j] * filter[row - i + 4 + 4 * (j - j)];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}