#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmpp;
  int range = 32 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 32; i < 8168 - 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 32; j < 8168 - 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < -16 + 1; k++) {
        tmpp = ((i + k) << 11) + ((j + 32) << 1);
        tmp += ((orig[tmpp]) * (filter[k + 32]));
      }
      sol[((i << 11)) + ((j << 1))] = tmp;
    }
  }
}