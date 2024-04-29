#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (i + ((-4 + k) << 8)) >> 8;
        if (idx < 0) {
          idx = 0;
        }
        else {
          if (idx > 255) {
            idx = 255;
          }
        }
        s += ((orig[idx] * filter[k])) << 2;
      }
      sol[i << 8 | j] = s >> 2;
    }
  }
}