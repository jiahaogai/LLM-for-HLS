Arrays:
- Arrays `orig` and `sol` are declared as pointers to `int` and have the size of 8192.
- Array `filter` is a local array and has the size of 9.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) > -1 ? -1 : 0);
        row = row < 0 ? 0 : row;
        row = row > 127 - 1 ? 127 - 1 : row;
        col = j + ((k - 4) > -1 ? -1 : 0);
        col = col < 0 ? 0 : col;
        col = col > 63 - 1 ? 63 - 1 : col;
        sum += filter[k] * orig[row * 64 + col];
      }
      sol[i * 64 + j] = sum;
    }
  }
}