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
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      idx = i * 8192 + j;
      val = ((orig[idx + 8191] + orig[idx + 8190]) + orig[idx + 1]) + ((orig[idx - 8191] + orig[idx - 8190]) + orig[idx - 1]);
      val = val + ((orig[idx + 8192] + orig[idx + 8184]) + orig[idx + 8182]) + ((orig[idx - 8192] + orig[idx - 8184]) + orig[idx - 8182]);
      sol[idx] = val;
    }
  }
}