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
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      idx = i * (128 + 2) + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + 1)) + (filter[2] * (center + 2))) + ((filter[3] * (center - 2)) + (filter[4] * (center - 1))) + ((filter[5] * (center + 1)) + (filter[6] * center)) + ((filter[7] * (center + 2)) + (filter[8] * (center + 1)));
    }
  }
}