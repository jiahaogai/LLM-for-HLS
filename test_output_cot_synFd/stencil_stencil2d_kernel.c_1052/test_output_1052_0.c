#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        x = i + k;
        y = j + (-4);
        if (((x >= 0) && (x < 256))) {
          if ((y >= 0)) {
            if (((y < 256))) {
              t += ((orig[x * 256 + y] * filter[k + 4]));
            }
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}