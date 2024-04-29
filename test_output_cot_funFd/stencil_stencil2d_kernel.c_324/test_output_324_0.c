#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 1; r < 128 + 1 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 64 + 1 - 1; c++) {
      value = ((0 * (orig[r - 1][c - 1] - sol[r - 1][c - 1])) + (1 * (orig[r - 1][c] - sol[r - 1][c])) + (2 * (orig[r - 1][c + 1] - sol[r - 1][c + 1])) + (3 * (orig[r][c - 1] - sol[r][c - 1])) + (4 * (orig[r][c] - sol[r][c])) + (5 * (orig[r][c + 1] - sol[r][c + 1])) + (6 * (orig[r + 1][c - 1] - sol[r + 1][c - 1])) + (7 * (orig[r + 1][c] - sol[r + 1][c])) + (8 * (orig[r + 1][c + 1] - sol[r + 1][c + 1]))) / 36;
      if (value < 0) {
        value = 0;
      }
      if (value > 255) {
        value = 255;
      }
      sol[r][c] = value;
    }
  }
}