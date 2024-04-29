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
  outer:
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      val = orig[idx] + filter[0] * orig[idx - 1] + filter[1] * orig[idx - 32] + filter[2] * orig[idx - 33];
      sol[idx] = val;
    }
  }
}