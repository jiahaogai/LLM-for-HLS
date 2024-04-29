#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      val = ((filter[0] * orig[idx - 32]) + (filter[1] * orig[idx - 16]) + (filter[2] * orig[idx - 8]) + (filter[3] * orig[idx - 4]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 4]) + (filter[6] * orig[idx + 8]) + (filter[7] * orig[idx + 16]) + (filter[8] * orig[idx + 32]));
      sol[idx] = val;
    }
  }
}