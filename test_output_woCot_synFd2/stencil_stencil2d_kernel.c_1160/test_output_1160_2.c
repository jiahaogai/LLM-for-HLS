#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int pad = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loopj:
  for (j = 0; j < 8; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 8; i++) {
      sum = 0;
      loopk:
      for (k = -4; k < 5; k++) {
        sum += filter[k + 4] * orig[pad + i + (pad + j) * 64 + k];
      }
      sol[pad + i + (pad + j) * 64] = sum;
    }
  }
}