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
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * (orig[idx - 8192] + orig[idx + 8192]) + filter[1] * (orig[idx - 1] + orig[idx + 1]) + filter[2] * orig[idx];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = sol[idx] + filter[0] * (sol[idx - 8192] + sol[idx + 8192]) + filter[1] * (sol[idx - 1] + sol[idx + 1]) + filter[2] * sol[idx];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = sol[idx] + filter[0] * (sol[idx - 8192] + sol[idx + 8192]) + filter[1] * (sol[idx - 1] + sol[idx + 1]) + filter[2] * sol[idx];
      sol[idx] = val / 4.0;
    }
  }
}