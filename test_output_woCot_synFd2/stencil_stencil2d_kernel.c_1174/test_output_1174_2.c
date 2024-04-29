#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner_1:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 8) * (k - 4) + (256 + 1 + 8) * j + i;
        s += ((double )filter[k]) * orig[idx];
      }
      sol[idx] = s;
    }
  }
}