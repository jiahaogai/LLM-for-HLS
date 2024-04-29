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
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (x = -1; x < 2; x++) {
        for (y = -1; y < 2; y++) {
          t += filter[y + 1] * orig[(i * 8) + x + 1 + ((j * 8) + y + 1) * 64];
        }
      }
      sol[(i * 8) + j * 64] = t;
    }
  }
}