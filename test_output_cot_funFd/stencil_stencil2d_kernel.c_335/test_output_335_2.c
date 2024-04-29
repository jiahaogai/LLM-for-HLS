#ifndef STENCIL_H
#define STENCIL_H

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((0 - filter[0]) * orig[i * 8192 + j]) + ((0 - filter[1]) * (orig[i * 8192 + j + 1]));
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 2; k < 9; k++) {
        result += ((0 - filter[k]) * orig[i * 8192 + j + (-1 + k)]);
      }
      sol[i * 8192 + j] = result;
    }
  }
}

#endif