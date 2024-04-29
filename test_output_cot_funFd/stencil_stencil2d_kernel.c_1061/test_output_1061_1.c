#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 - 1; j++) {
      idx = i * 64 + j;
      sol[idx] = ((filter[0] * orig[idx - 64]) + (filter[1] * orig[idx - 16]) + (filter[2] * orig[idx]) + (filter[3] * orig[idx + 16]) + (filter[4] * orig[idx + 64])) / ((float )16);
/* Standardize from: ((filter[0] * (256 - 16) * orig[idx - 64]) + (filter[1] * (256 - 16) * orig[idx - 16]) + (filter[2] * (256 - 16) * orig[idx]) + (filter[3] * (256 - 16) * orig[idx + 16]) + (filter[4] * (256 - 16) * orig[idx + 64])) / ((float )16) */
    }
  }
}