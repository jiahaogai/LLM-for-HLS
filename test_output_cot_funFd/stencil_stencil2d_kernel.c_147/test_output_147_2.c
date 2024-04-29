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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 32; j < 8160 - 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < 33; k++) {
        tmpp = k * 8;
        tmp += filter[tmpp + 32] * orig[i + k * 8];
      }
      sol[i * 8 + j] = tmp;
    }
  }
}