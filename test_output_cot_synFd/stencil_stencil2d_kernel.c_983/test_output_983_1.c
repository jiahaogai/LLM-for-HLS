#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + (j * 32);
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + orig[idx + 1])) + (filter[2] * (center + orig[idx + 1 + 32]))) + ((filter[3] * (center + orig[idx + 32])) + (filter[4] * (center + orig[idx + 1 - 32])));
    }
  }
}