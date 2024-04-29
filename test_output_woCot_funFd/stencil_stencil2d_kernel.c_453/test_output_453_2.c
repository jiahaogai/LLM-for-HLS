#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + ((k + 1) % 9) - 1;
        idy = j + ((k + 1) / 9) - 1;
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 255) {
          idx = 255;
        }
        if (idy < 0) {
          idy = 0;
        }
        if (idy > 255) {
          idy = 255;
        }
        s += filter[k] * orig[idx * 256 + idy];
      }
      sol[i * 256 + j] = s;
    }
  }
}