<<<<<<< HEAD
#include <math.h>
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int t;
=======
  int flatten_i;
  int flatten_j;
  int idx = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
=======
  loop:for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 32));
        i_col = ((8 * k) + (i % 32));
        j_col = ((8 * j) + (k % 32));
        t += filter[k] * orig[k_col * 8192 + i_col] * orig[j_col * 8192 + i_col];
      }
      sol[i * 8192 + j] = t;
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner1:for (j = 0; j < 256; j++) {
      flatten_i = i * 256;
      flatten_j = j * 16;
      int sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner2:for (k = 0; k < 9; k++) {
        int cur = filter[k] * orig[flatten_i + flatten_j + k];
        sum = sum + cur;
      }
sol[idx] = sum;
idx++;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}