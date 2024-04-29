#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      idx = (i - 1) * 8186 + (j - 1);
      val = orig[idx] + filter[0] * (orig[idx - 8186] + orig[idx + 8186]) + filter[1] * (orig[idx - 1] + orig[idx + 1]) + filter[2] * orig[idx];
      sol[idx] = val;
    }
  }
}