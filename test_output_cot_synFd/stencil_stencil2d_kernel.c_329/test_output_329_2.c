#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (flit = 0; flit < 9; flit++) {
        row = i + ((-1 + 2 * (flit % 3)) >> 1);
        col = j + ((-1 + 2 * (flit / 3)) >> 1);
        if (row < 0 || 256 <= row || col < 0 || 256 <= col) {
          t += 0;
        }
         else {
          t += orig[row * 256 + col] * filter[flit];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}