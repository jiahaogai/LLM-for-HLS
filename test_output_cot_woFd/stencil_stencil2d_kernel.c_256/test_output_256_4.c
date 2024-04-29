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
/* Standardize from: for(j = 1;j < 64 + 1 - 3;j++) {...} */
  for (j = 1 + 3 - 1; j < 64 + 1 - 3; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 128 + 1 - 3;k++) {...} */
    for (k = 1 + 3 - 1; k < 128 + 1 - 3; k++) {
      idx = k + ((j + 1) << 7);
      val = orig[idx] + filter[0] * (orig[idx + 1] + orig[idx - 1]) + filter[1] * (orig[idx + 8] + orig[idx - 8]) + filter[2] * (orig[idx + 16] + orig[idx - 16]);
      sol[idx] = val;
    }
  }
}