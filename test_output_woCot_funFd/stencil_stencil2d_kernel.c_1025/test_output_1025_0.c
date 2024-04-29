#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + j;
      if (((x >= 0) && (x < 8192))) {
        t += ((orig[x]) * (filter[j]));
      }
    }
    y = i - 4;
    sol[y] = t;
  }
}