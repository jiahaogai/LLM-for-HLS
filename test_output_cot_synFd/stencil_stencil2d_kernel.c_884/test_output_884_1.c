#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int x;
  int y;
  int t;
  int pt[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        x = (-4 + ((k >> 1) & 1)) + ((k & 1) * 8);
        y = (-4 + ((k >> 2) & 1)) + ((k & 2) * 8);
        index = i + x;
        if (index < 0) {
          index = 0;
        }
        else {
          if (index > 255) {
            index = 255;
          }
        }
        y = j + y;
        if (y < 0) {
          y = 0;
        }
        else {
          if (y > 255) {
            y = 255;
          }
        }
        t = filter[k] * orig[index * 256 + y];
        pt[k] = t;
      }
      t = pt[0] + pt[1] + pt[2];
      t += pt[7] + pt[8] + pt[4] - pt[5] - pt[6];
      sol[i * 256 + j] = t;
    }
  }
}