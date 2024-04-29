#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      idx = (8192 * (j - 1)) + i;
      sol[idx] = ((filter[0] * orig[idx - 8190]) + (filter[1] * (orig[idx - 8190 + 1] + orig[idx + 1])) + (filter[2] * orig[idx - 8190 + 2]) + (filter[3] * (orig[idx - 1] + orig[idx + 8190])) + (filter[4] * orig[idx]) + (filter[5] * (orig[idx + 8190 - 1] + orig[idx - 8190 + 1])) + (filter[6] * (orig[idx + 8190 - 2] + orig[idx - 8190 + 2])) + (filter[7] * (orig[idx + 8190 - 3] + orig[idx - 8190 + 3])) + (filter[8] * orig[idx + 8190 - 4]));
    }
  }
}