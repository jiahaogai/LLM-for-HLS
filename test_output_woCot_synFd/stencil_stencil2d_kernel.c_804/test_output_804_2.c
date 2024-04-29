#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + j * 32;
      x = orig[idx] + filter[0] * orig[idx - 1] + filter[1] * (orig[idx - 32] + orig[idx + 1]) + filter[2] * (orig[idx - 33] + orig[idx + 32]);
      y = x + filter[3] * (orig[idx - 32] + orig[idx + 32]);
      sol[idx] = y;
    }
  }
}