#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    idx = i % 64;
    inner:
    for (j = 0; j < 8192; j++) {
      int sum = 0.0;
      middle:
      for (k = 0; k < 9; k++) {
        int cur = orig[(((idx + ((k + 4) - center) & 63)) * 8192) + ((j + ((k + 4) - center)) & 8191)];
        sum += cur * filter[k];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}