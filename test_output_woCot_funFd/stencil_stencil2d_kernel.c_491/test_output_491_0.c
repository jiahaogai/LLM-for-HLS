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
      x = i - 4 + ((j + 4) >> 4);
      y = ((j + 4) & 15);
      if (x < 0 || x > 8191) {
        t += filter[j] * 0;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      else {
        t += filter[j] * orig[x * 16 + y];
      }
    }
    sol[i] = t;
  }
}