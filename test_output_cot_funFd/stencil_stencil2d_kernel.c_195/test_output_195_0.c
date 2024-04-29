#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 32; i++) {
      idx = i + j * 32;
      val = orig[idx] + filter[0] * orig[idx - 1 + 0] + filter[1] * orig[idx - 1 + 1] + filter[2] * orig[idx - 1 + 2] + filter[3] * orig[idx + 1 + 2] + filter[4] * orig[idx + 1 + 1] + filter[5] * orig[idx + 1 + 0] + filter[6] * orig[idx + 2 + 0] + filter[7] * orig[idx + 2 + 1] + filter[8] * orig[idx + 2 + 2];
      sol[idx] = val;
    }
  }
}