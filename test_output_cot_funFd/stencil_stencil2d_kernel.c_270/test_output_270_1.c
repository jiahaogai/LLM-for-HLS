#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmpp;
  int range;
  range = 32 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 32; i < 8160 - 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 32; j < 8160 - 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < 33; k++) {
        tmpp = k * 8;
        tmp += orig[i + k + tmpp] * filter[tmpp];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}