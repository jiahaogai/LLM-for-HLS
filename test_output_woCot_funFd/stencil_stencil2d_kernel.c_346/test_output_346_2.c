#include <math.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int center = 4;
=======
  int sum;
  int flatten_i;
  int flatten_j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    for (j = 1; j < 32 + 1 - 1; j++) {
      idx = i * 32 + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + ((k - 4) * 32)];
      }
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}