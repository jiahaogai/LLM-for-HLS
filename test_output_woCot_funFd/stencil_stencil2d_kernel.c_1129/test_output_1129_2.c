Code: #pragma ACCEL kernel
 #pragma ACCEL PIPELINE auto{}
 #pragma ACCEL TILE FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{7}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      idx = (i - 1) * 8176 + j - 1;
      val = orig[idx] + filter[0] * (orig[idx - 8176] + orig[idx + 8176]) + filter[1] * (orig[idx - 1] + orig[idx + 1]) + filter[2] * orig[idx];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      idx = (i - 1) * 8176 + j - 1;
      val = sol[idx] + filter[0] * (sol[idx - 8176] + sol[idx + 8176]) + filter[1] * (sol[idx - 1] + sol[idx + 1]) + filter[2] * sol[idx];
      sol[idx] = (val + 8) / 16;
    }
  }
}