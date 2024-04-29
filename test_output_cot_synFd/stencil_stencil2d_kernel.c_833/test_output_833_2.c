#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 16; i < 8172 - 16; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 16; j < 8192 - 16; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + -1)) + (filter[2] * (center + -8192))) + ((filter[3] * (center + 8192)) + (filter[4] * (center + 1)) + (filter[5] * (center + -8192 + 1)));
    }
  }
}