#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int idx;
  int center;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (j = 0; j < 9; j++) {
        if (j != 4) {
          flit += filter[j] * orig[idx + 8192 * (j - 4)];
        }
      }
      sol[idx] = flit;
    }
  }
}