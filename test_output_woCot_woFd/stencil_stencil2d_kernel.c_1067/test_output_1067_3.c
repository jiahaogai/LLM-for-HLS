#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (x = -1; x < 2; x++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (y = -1; y < 2; y++) {
          t += filter[((y + 1) * 3) + (x + 1)] * orig[i + x + ((j + y) * 256)];
        }
      }
      sol[i + j * 256] = t;
    }
  }
}