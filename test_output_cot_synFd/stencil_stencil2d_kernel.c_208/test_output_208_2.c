#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) * 8);
        col = j + ((k - 4) * 8);
        if (row < 0) {
          row = 0;
        }
        if (row > 8191) {
          row = 8191;
        }
        if (col < 0) {
          col = 0;
        }
        if (col > 8191) {
          col = 8191;
        }
        t += filter[k] * orig[row * 8192 + col];
      }
      sol[i * 8192 + j] = t;
    }
  }
}