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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = ((filter[0] * orig[idx - 256 - 1]) + (filter[1] * orig[idx - 256]) + (filter[2] * orig[idx - 256 + 1])) + ((filter[3] * orig[idx - 1]) + (filter[4] * orig[idx + 0]) + (filter[5] * orig[idx + 1])) + ((filter[6] * orig[idx + 256 - 1]) + (filter[7] * orig[idx + 256]) + (filter[8] * orig[idx + 256 + 1]));
      val = val > 0 ? val : 0;
      sol[idx] = val;
    }
  }
}