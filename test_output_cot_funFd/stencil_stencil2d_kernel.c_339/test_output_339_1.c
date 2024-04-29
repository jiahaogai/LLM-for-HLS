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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (flit = 0; flit < 9; flit++) {
        row = i + ((-1 + flit) / 3);
        col = j + ((-1 + flit) % 3);
        if (((row < 256) && (row >= 0)) && ((col < 256) && (col >= 0))) {
          t += filter[flit] * orig[row * 256 + col];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}