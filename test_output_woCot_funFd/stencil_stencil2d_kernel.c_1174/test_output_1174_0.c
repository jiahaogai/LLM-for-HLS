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
      val = ((filter[0] * orig[idx - 8 - 8192]) + (filter[1] * orig[idx - 8 - 1]) + (filter[2] * orig[idx - 8])) + ((filter[3] * orig[idx - 1 - 8192]) + (filter[4] * orig[idx - 1]) + (filter[5] * orig[idx - 1])) + ((filter[6] * orig[idx + 8 - 8192]) + (filter[7] * orig[idx + 8 - 1]) + (filter[8] * orig[idx + 8]));
      sol[idx] = val;
    }
  }
}