#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (x = -1; x <= 1; x++) {
        inner_1:
        for (y = -1; y <= 1; y++) {
          t += filter[((y + 1) * 3) + x + 1] * orig[i * 64 + j * 8 + x + ((y + 1) * 8)];
        }
      }
      sol[i * 64 + j * 8] = t;
    }
  }
}