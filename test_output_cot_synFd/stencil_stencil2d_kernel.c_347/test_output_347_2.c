Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * (orig[idx - 1] + orig[idx + 1]) + filter[1] * (orig[idx - 8192] + orig[idx + 8192]) + filter[2] * (orig[idx - 8194] + orig[idx + 8194]);
      sol[idx] = val;
    }
  }
}