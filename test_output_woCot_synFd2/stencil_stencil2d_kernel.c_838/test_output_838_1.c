#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 32; i++) {
      idx = (j * 32) + i;
      val = orig[idx] + filter[0] * (orig[idx - 1] + orig[idx + 1]) + filter[1] * (orig[idx - 32] + orig[idx + 32]) + filter[2] * (orig[idx - 33] + orig[idx + 33]);
      sol[idx] = val;
    }
  }
}