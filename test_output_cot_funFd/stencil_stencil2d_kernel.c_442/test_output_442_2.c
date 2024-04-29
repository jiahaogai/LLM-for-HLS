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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1 - 1; j++) {
      idx = i * 32 + j;
      val = orig[idx] + filter[0] * (orig[idx - 32 - 1] + orig[idx - 32] + orig[idx - 32 + 1] + orig[idx - 1] + orig[idx + 1] + orig[idx + 32 - 1] + orig[idx + 32] + orig[idx + 32 + 1]) + filter[1] * (orig[idx - 1 - 32] + orig[idx - 1] + orig[idx - 1 + 32] + orig[idx + 32 - 1] + orig[idx + 32] + orig[idx + 32 + 1] + orig[idx + 1 - 32] + orig[idx + 1] + orig[idx + 1 + 32]);
      sol[idx] = val;
    }
  }
}