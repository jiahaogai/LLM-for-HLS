#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = ((orig[idx + 8192] + orig[idx + 8192 - 1]) + orig[idx + 1]) + ((orig[idx - 8192] + orig[idx - 8192 + 1]) + orig[idx - 1]);
      val -= (filter[0] * orig[idx]);
      sol[idx] = val;
    }
  }
}