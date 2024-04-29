#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8; i++) {
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[((i + pad) * 64) + ((j + pad) * 8) + k];
      }
      sol[((i * 8) + j)] = t;
    }
  }
}