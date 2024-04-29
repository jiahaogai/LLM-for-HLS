#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      val = orig[idx] + filter[0] * orig[idx - 128] + filter[1] * orig[idx - 1] + filter[2] * orig[idx + 1] + filter[3] * orig[idx + 128] + filter[4] * orig[idx - 16] + filter[5] * orig[idx + 16] + filter[6] * orig[idx - 8] + filter[7] * orig[idx + 8];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{62}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      val = sol[idx] + filter[0] * sol[idx - 128] + filter[1] * sol[idx - 1] + filter[2] * sol[idx + 1] + filter[3] * sol[idx + 128] + filter[4] * sol[idx - 16] + filter[5] * sol[idx + 16] + filter[6] * sol[idx - 8] + filter[7] * sol[idx + 8];
      orig[idx] = val;
    }
  }
}