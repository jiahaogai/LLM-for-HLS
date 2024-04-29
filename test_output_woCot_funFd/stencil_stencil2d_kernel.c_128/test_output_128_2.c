<<<<<<< HEAD
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, not in parts.
- `#pragma ACCEL PIPELINE auto{}`: Allow automatic pipelining for the loop `stencil_label3`.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide the iterations of the loop `stencil_label3` into chunks of size 8.
=======
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the loop `stencil_label3` sequentially, not concurrently.
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int val;
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += filter[k] * orig[i * 256 + idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}
=======
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 * (i + 4)) + (j + k);
        if (idx < 0) {
          idx = 0;
        }
         else {
          if (idx > 8191) {
            idx = 8191;
          }
        }
        sum += orig[idx] * filter[k + 4];
      }
      sol[i * 256 + j] = sum;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the loop `stencil_label3` sequentially, not concurrently.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 * (i + 4)) + (j + k);
        if (idx < 0) {
          idx = 0;
        }
         else {
          if (idx > 8191) {
            idx = 8191;
          }
        }
        sum += orig[idx] * filter[k + 4];
      }
      sol[i * 256 + j] = sum;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARAL
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
