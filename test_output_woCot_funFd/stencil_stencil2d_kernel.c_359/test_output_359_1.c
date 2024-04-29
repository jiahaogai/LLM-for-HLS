#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      idx = (8192 + center - (i - 1)) % 8192;
      sol[idx] = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * (orig[idx + 2] + orig[idx - 2])) + (filter[3] * (orig[idx + 3] + orig[idx - 3])) + (filter[4] * (orig[idx + 4] + orig[idx - 4])) + (filter[5] * (orig[idx + 5] + orig[idx - 5])) + (filter[6] * (orig[idx + 6] + orig[idx - 6])) + (filter[7] * (orig[idx + 7] + orig[idx - 7])) + (filter[8] * orig[idx + 8])) % 255;
    }
  }
}