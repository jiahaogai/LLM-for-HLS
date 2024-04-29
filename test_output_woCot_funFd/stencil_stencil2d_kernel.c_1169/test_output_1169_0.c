#ifndef ACCEL_STENCIL_H
#define ACCEL_STENCIL_H

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8188; j++) {
      result = ((orig[i * 8192 + j] + orig[i * 8192 + j + 1] + orig[i * 8192 + j + 8192] + orig[i * 8192 + j + 8193]) + (orig[i * 8192 + j + 8194] + orig[i * 8192 + j + 8195] + orig[i * 8192 + j + 8196] + orig[i * 8192 + j + 8197])) + (orig[i * 8192 + j + 8198] + orig[i * 8192 + j + 8199] + orig[i * 8192 + j + 8200] + orig[i * 8192 + j + 8201]);
      sol[i * 8192 + j] = result;
    }
  }
}

#endif