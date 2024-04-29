#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 16; i < 8192 - 16; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 16; j < 8192 - 16; j++) {
      idx = i * 8192 + j;
      val = ((filter[0] * orig[idx - 8192 - 1]) + (filter[1] * orig[idx - 8192]) + (filter[2] * orig[idx - 8192 + 1]) + (filter[3] * orig[idx - 1]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 1]) + (filter[6] * orig[idx + 8192 - 1]) + (filter[7] * orig[idx + 8192]) + (filter[8] * orig[idx + 8192 + 1])) >> 12;
      sol[idx] = val;
    }
  }
}