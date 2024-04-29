#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      idx = i * 337 + j;
      val = orig[idx] + filter[0] * orig[idx - 337 - 1] + filter[1] * orig[idx - 337] + filter[2] * orig[idx - 337 + 1] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 337 - 1] + filter[6] * orig[idx + 337] + filter[7] * orig[idx + 337 + 1];
      sol[idx] = val;
    }
  }
}