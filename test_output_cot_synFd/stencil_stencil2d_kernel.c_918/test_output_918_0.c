#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + 1)) + (filter[2] * (center + 2))) + ((filter[3] * center) + (filter[4] * (center + 1)) + (filter[5] * (center + 2))) + ((filter[6] * center) + (filter[7] * (center + 1)) + (filter[8] * (center + 2)));
    }
  }
}