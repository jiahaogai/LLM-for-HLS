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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 32; i++) {
      idx = i + (j * 32);
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        int cur = filter[k] * orig[idx + align(k - center, 32)];
        sol[idx] += cur;
      }
    }
  }
}