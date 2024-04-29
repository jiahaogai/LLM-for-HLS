#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = ((orig[idx + 8192] + orig[idx + 768] + orig[idx + 8]) + (orig[idx - 8192] + orig[idx - 768] + orig[idx - 8])) + (orig[idx] + orig[idx + 1] + orig[idx - 1]);
      sol[idx] = filter[val];
    }
  }
}