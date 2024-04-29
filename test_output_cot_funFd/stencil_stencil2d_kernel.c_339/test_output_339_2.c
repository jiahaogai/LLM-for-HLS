#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int t;
  int p;
  
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
      for (p = -4; p < 5; p++) {
        x = i + p;
        if (x < 0 || x > 255) {
          x = 0;
        }
        y = j - 4;
        if (y < 0 || y > 255) {
          y = 0;
        }
        t += ((orig[x * 256 + y]) * filter[p + 4]);
      }
      sol[i * 256 + j] = t;
    }
  }
}