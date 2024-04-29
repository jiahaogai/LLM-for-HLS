<<<<<<< HEAD
=======
#include <math.h>
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{62}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
<<<<<<< HEAD
        result += filter[k] * orig[i + ((k - 4) * 8191)];
      }
      sol[j] = result;
    }
    sol[8191] = result;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8191; j++) {
      orig[j] = sol[j];
=======
        result += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}