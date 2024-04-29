#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 128; j++) {
      result = ((0 * orig[i * 128 + j]) + (1 * orig[(i + 1) * 128 + j]) + (2 * orig[(i + 2) * 128 + j]) + (3 * orig[(i + 3) * 128 + j]) + (4 * orig[(i + 4) * 128 + j]) + (5 * orig[(i + 5) * 128 + j]) + (6 * orig[(i + 6) * 128 + j]) + (7 * orig[(i + 7) * 128 + j]) + (8 * orig[(i + 8) * 128 + j])) / 32;
      sol[i * 128 + j] = result;
    }
  }
}