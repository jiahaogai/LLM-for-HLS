#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      idx = (i - 1) * (128 + 2) + j - 1;
      val = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * orig[idx + 2]) + (filter[3] * (orig[idx + 1 + 1] + orig[idx - 1 - 1])) + (filter[4] * (orig[idx + 2 + 1] + orig[idx - 2 - 1])) + (filter[5] * (orig[idx + 1 + 2] + orig[idx - 1 - 2])) + (filter[6] * (orig[idx + 2 + 2] + orig[idx - 2 - 2])) + (filter[7] * orig[idx + 2 + 2 + 1])) >> 15;
      sol[idx] = val;
    }
  }
}