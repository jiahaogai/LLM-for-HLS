#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 64 - 1; j++) {
      idx = i * 64 + j;
      val = orig[idx] + filter[0] * orig[idx - 64] + filter[1] * orig[idx - 1] + filter[2] * orig[idx + 1] + filter[3] * orig[idx + 64] + filter[4] * orig[idx - 61] + filter[5] * orig[idx - 1 + 61] + filter[6] * orig[idx + 1 + 61] + filter[7] * orig[idx + 61];
      sol[idx] = val;
    }
  }
}