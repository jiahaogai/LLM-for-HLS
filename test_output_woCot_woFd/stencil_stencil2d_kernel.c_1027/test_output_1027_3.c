#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 8192; i++) {
    result = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        continue;
      }
      result += filter[j] * orig[k];
    }
    sol[i] = result;
  }
}