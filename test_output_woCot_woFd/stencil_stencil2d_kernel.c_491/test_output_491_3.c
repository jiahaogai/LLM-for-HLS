#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + ((j % 3) - 1);
      y = i - 4 + ((j / 3) - 1);
      if (x >= 0 && x < 8192 && y >= 0 && y < 8192) {
        t += filter[j] * orig[y * 8192 + x];
      }
    }
    sol[i] = t;
  }
}