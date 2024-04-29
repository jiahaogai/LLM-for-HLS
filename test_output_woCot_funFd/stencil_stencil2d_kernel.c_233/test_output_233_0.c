#ifndef STENCIL_H
#define STENCIL_H

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8176; j++) {
      result = ((filter[0] * orig[i * 8192 + j]) + (filter[1] * orig[i * 8192 + j + 1]) + (filter[2] * orig[i * 8192 + j + 2]) + (filter[3] * orig[i * 8192 + j + 8176]) + (filter[4] * orig[i * 8192 + j + 8177]) + (filter[5] * orig[i * 8192 + j + 8178]) + (filter[6] * orig[i * 8192 + j + 8192]) + (filter[7] * orig[i * 8192 + j + 8193]) + (filter[8] * orig[i * 8192 + j + 8194]));
      sol[i * 8192 + j] = result;
    }
  }
}

#endif