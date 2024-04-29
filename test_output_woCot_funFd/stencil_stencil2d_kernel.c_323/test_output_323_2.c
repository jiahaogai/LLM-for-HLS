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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1; j++) {
      idx = i * (32 + 2) + j;
      val = orig[idx] + filter[0] * orig[idx - 1 - (32 + 2)] + filter[1] * orig[idx - 1] + filter[2] * orig[idx - 1 + (32 + 2)] + filter[3] * orig[idx + (32 + 2)] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 1 + (32 + 2)] + filter[6] * orig[idx + 1 - (32 + 2)];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 32 + 1; i < 64 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1; j++) {
      idx = i * (32 + 2) + j;
      val = orig[idx] + filter[0] * sol[idx - 1 - (32 + 2)] + filter[1] * sol[idx - 1] + filter[2] * sol[idx - 1 + (32 + 2)] + filter[3] * sol[idx + (32 + 2)] + filter[4] * sol[idx + 1] + filter[5] * sol[idx + 1 + (32 + 2)] + filter[6] * sol[idx + 1 - (32 + 2)];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 64 + 1; i < 96 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1; j++) {
      idx = i * (32 + 2) + j;
      val = orig[idx] + filter[0] * sol[idx - 1 - (32 + 2)] + filter[1] * sol[idx - 1] + filter[2] * sol[idx - 1 + (32 + 2)] + filter[3] * sol[idx + (32 + 2)] + filter[4] * sol[idx + 1] + filter[5] * sol[idx + 1 + (32 + 2)] + filter[6] * sol[idx + 1 - (32 + 2)];
      sol[idx] = val;
    }
  }
}