#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      result = ((orig[i - 8] + orig[i + 8]) + (orig[i - 1] + orig[i + 1])) + orig[i];
      sol[i + 1] = filter[result];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      result = ((sol[i - 8 + 1] + sol[i + 8 + 1]) + (sol[i - 1 + 1] + sol[i + 1 + 1])) + sol[i + 1];
      sol[i + 1] = filter[result];
    }
  }
}