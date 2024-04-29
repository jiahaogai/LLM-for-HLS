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
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (flit = 0; flit < 9; flit++) {
        row = i + ((-1 + flit) / 9);
        col = j + ((-1 + flit) % 9);
        if (((row >= 0) && (row < 8192)) && ((col >= 0) && (col < 8192))) {
          t += orig[row * 8192 + col] * filter[flit];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}