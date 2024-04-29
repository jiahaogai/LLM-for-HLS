The kernel is written in C99, and the ACCEL compiler accepts a subset of C99.
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = ((filter[0] * orig[idx - 8192]) + (filter[1] * orig[idx - 8191]) + (filter[2] * orig[idx - 8190]) + (filter[3] * orig[idx - 8189]) + (filter[4] * orig[idx - 8188]) + (filter[5] * orig[idx - 8187]) + (filter[6] * orig[idx - 8186]) + (filter[7] * orig[idx - 8185]) + (filter[8] * orig[idx - 8184])) + orig[idx];
    }
  }
}