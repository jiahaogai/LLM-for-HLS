#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      val = orig[idx] + filter[0] * orig[idx - 128] + filter[1] * orig[idx - 128 + 1] + filter[2] * orig[idx - 128 + 2] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 2] + filter[6] * orig[idx + 128] + filter[7] * orig[idx + 128 + 1] + filter[8] * orig[idx + 128 + 2];
      sol[idx] = val;
    }
  }
}