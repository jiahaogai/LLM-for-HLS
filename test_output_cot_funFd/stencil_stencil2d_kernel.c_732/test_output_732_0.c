#pragma ACCEL kernel
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      idx = i * 8190 + j;
      val = orig[idx] + filter[0] * orig[idx - 8190] + filter[1] * orig[idx - 8190 + 1] + filter[2] * orig[idx - 8190 + 2] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 2] + filter[6] * orig[idx + 8190] + filter[7] * orig[idx + 8190 + 1] + filter[8] * orig[idx + 8190 + 2];
      sol[idx] = val;
    }
  }
}