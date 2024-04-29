#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (row = -4; row < 5; row++) {
        for (col = -4; col < 5; col++) {
          int index = (i + row) * 8192 + (j + col);
          t += filter[row * 9 + col] * orig[index];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}