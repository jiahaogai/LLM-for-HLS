Code: 
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
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      val = orig[idx] + filter[0] * orig[idx - 1] + filter[1] * orig[idx - 32] + filter[2] * orig[idx - 33];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      val = sol[idx] + filter[0] * sol[idx - 1] + filter[1] * sol[idx - 32] + filter[2] * sol[idx - 33];
      sol[idx] = val;
    }
  }
}