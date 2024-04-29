#ifndef STENCIL_H
#define STENCIL_H
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  int index;
  int pass;
  int flatten_main_result;
  
#pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flatten_main_result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  pass = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (pass < 40) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 33; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (j = 1; j < 33; j++) {
        index = i * 32 + j;
        result = ((filter[0] * orig[index - 33 - 1]) + (filter[1] * orig[index - 33]) + (filter[2] * orig[index - 33 + 1]) + (filter[3] * orig[index - 1]) + (filter[4] * orig[index + 1]) + (filter[5] * orig[index + 33 - 1]) + (filter[6] * orig[index + 33]) + (filter[7] * orig[index + 33 + 1]) + (filter[8] * orig[index])) >> 4;
        sol[index] = result;
      }
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    pass++;
  }
}
#endif