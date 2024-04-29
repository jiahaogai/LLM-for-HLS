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
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + (j * 32);
      sol[idx] = ((filter[0] * orig[idx - 1 - 32]) + (filter[1] * orig[idx - 32]) + (filter[2] * orig[idx + 1 - 32]) + (filter[3] * orig[idx - 1]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 1]) + (filter[6] * orig[idx - 1 + 32]) + (filter[7] * orig[idx + 32]) + (filter[8] * orig[idx + 1 + 32])) / 42;
    }
  }
}