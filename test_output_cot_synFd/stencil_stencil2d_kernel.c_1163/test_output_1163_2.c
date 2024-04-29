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
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8178; j++) {
      idx = (8190 * (j - 1)) + i;
      val = orig[idx] + filter[0] * orig[idx + 8190] + filter[1] * orig[idx + 1] + filter[2] * orig[idx - 8190] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 8178] + filter[5] * orig[idx - 8178] + filter[6] * orig[idx + 16386] + filter[7] * orig[idx - 16386] + filter[8] * orig[idx + 16384];
      sol[idx] = val;
    }
  }
}