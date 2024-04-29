#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (x = -1; x <= 1; x++) {
        y = -1;
        while (y <= 1) {
          t += filter[((x + 1) * 3) + (y + 1)] * orig[((i * 64) + 16) + ((j * 64) + (x * 8) + y)];
          y++;
        }
      }
      sol[((i * 64) + 16) + ((j * 64) + 8)] = t;
    }
  }
}