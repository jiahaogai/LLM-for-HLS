#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loop_i:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 256; j++) {
      flatten_i = i * 256;
      flatten_j = j * 1;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loop_k:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[flatten_i + (flatten_j + k)];
      }
      sol[flatten_i + flatten_j] = sum;
    }
  }
}