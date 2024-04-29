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
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx - 8190] + filter[3] * orig[idx - 8189] + filter[4] * orig[idx - 8188] + filter[5] * orig[idx - 8187] + filter[6] * orig[idx - 8186] + filter[7] * orig[idx - 8185] + filter[8] * orig[idx - 8184];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = sol[idx] + filter[0] * sol[idx - 8192] + filter[1] * sol[idx - 8191] + filter[2] * sol[idx - 8190] + filter[3] * sol[idx - 8189] + filter[4] * sol[idx - 8188] + filter[5] * sol[idx - 8187] + filter[6] * sol[idx - 8186] + filter[7] * sol[idx - 8185] + filter[8] * sol[idx - 8184];
      sol[idx] = (val + 8192) >> 14;
    }
  }
}