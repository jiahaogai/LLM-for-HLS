#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 32 + 1 - 1; j++) {
      s = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (((32 + 1 - 1) * (i - 1) + (k / 32 + 1 - 1)) * (32 + 1 - 1) + ((k % 32) + 1 - 1));
        s += filter[k] * orig[idx];
      }
      sol[((32 + 1 - 1) * (i - 1) + (j - 1)) * (32 + 1 - 1)] = s;
    }
  }
}