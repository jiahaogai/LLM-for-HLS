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
  loopj1:
  for (j = 32; j < 8160 - 32; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi1:
    for (i = 32; i < 8160 - 32; i++) {
      tmp = 0;
      tmpp = 0;
      loopk1:
      for (k = 0; k < 9; k++) {
        tmp += ((orig[i + ((k - 4) * 64)]) >> 4) * filter[k];
        tmpp += ((orig[i + ((k - 4) * 64) + 32]) >> 4) * filter[k];
      }
      sol[j * 64 + i] = ((tmp) >> 8) + ((tmpp) >> 8);
    }
  }
}