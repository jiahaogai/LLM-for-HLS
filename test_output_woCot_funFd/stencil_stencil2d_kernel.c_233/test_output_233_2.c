Code: #pragma ACCEL kernel
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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (row = -1; row <= 1; row++) {
        for (col = -1; col <= 1; col++) {
          t += filter[row + 1][col + 1] * orig[i * 64 + (row + 1) * 8 + col + 1];
        }
      }
      sol[i * 64 + j * 8] = t;
    }
  }
}