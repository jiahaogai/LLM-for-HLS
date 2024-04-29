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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (row = i * 64; row < (i + 1) * 64; row++) {
        for (col = j * 64; col < (j + 1) * 64; col++) {
          t += orig[row * 8192 + col] * filter[row - i * 64 + col - j * 64];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}