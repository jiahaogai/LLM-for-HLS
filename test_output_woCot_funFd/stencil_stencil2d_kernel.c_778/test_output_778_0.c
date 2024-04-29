#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 16; i < 8192 - 16; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 16; j < 8192 - 16; j++) {
      idx = (i - 16) * 64 + j - 16;
      sol[idx] = ((filter[0] * orig[idx - 32 - 16]) + (filter[1] * orig[idx - 32]) + (filter[2] * orig[idx - 32 + 16]) + (filter[3] * orig[idx - 16]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 16]) + (filter[6] * orig[idx + 32 - 16]) + (filter[7] * orig[idx + 32]) + (filter[8] * orig[idx + 32 + 16])) / 256;
    }
  }
}