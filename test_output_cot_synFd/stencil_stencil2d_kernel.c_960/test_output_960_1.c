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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 31; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 31; j++) {
      idx = i * 32 + j;
      val = ((orig[idx - 32] + orig[idx - 1]) + orig[idx]) + orig[idx + 1] + orig[idx + 32];
      sol[idx] = filter[val];
    }
  }
}