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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 32; i < 8160 - 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 32; j < 8160 - 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < -16 + 1; k++) {
        tmpp = k + j;
        if (tmpp >= 8160) {
          tmpp = 8159;
        }
        else {
          if (tmpp < 0) {
            tmpp = 0;
          }
        }
        tmp += ((orig[tmpp]) * filter[k + 32]);
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}