#ifndef STENCIL_H
#define STENCIL_H

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-1 + k) * 8190];
      }
      sol[i * 8190 + j] = result;
    }
  }
}

#endif