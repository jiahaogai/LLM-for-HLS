<<<<<<< HEAD
- Perform the stencil computation.

#pragma ACCEL kernel
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 8192; j++) {
      result = 0;
      middle:
      for (k = -4; k < 5; k++) {
        int cur = orig[i + k];
        result += filter[k + 4] * cur;
      }
      sol[i * 8192 + j] = result;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
