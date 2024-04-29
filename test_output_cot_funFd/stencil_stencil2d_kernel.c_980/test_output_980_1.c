### #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  int d;
  int delta;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = i - 1;
      if (t < 0) {
        t = 0;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (x = 0; x < 4; x++) {
        d = j - 1;
        if (d < 0) {
          d = 0;
        }
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        inner_1:
        for (y = 0; y < 4; y++) {
          delta = filter[d * 4 + y] * orig[t * 8 + x];
          sol[i * 8 + y] += delta;
        }
      }
    }
  }
}