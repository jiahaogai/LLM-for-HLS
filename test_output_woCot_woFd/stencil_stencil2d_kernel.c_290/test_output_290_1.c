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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx + 1] + filter[3] * orig[idx + 8191] + filter[4] * orig[idx + 8192] + filter[5] * orig[idx - 1] + filter[6] * orig[idx] + filter[7] * orig[idx + 8192];
      sol[idx] = val;
    }
  }
}