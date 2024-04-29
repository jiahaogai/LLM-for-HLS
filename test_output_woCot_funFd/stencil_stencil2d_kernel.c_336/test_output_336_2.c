<<<<<<< HEAD
For more information about the #pragma ACCEL directives, refer to the [Pragma ACCEL Document](https://www.xilinx.com/support/documentation/sw_manuals/acceleration_checker/v2_10/pg025-pragmas.html)

=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int sum;
=======
  int t;
  int x;
  int y;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
<<<<<<< HEAD
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
=======
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (x = -1; x < 2; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{32}
        for (y = -1; y < 2; y++) {
          t += filter[x + 1] * filter[y + 1] * orig[(i + x) * 8192 + (j + y)];
        }
      }
      sol[i * 8192 + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}