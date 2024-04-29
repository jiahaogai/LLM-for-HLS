<<<<<<< HEAD
The HLS tool automatically synthesizes a hardware implementation for the function based on the pragma directives and the function's code.

The pragma directives used in this function are:

 
=======
The `orig` array is the 2D input data to the function. The `sol` array is the 2D output data from the function. The `filter` array is a 1D array of integers representing the 2D filter. The function applies the filter to each element of the `orig` array and stores the result in the corresponding element of the `sol` array.

>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
=======
  int k;
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      sol[i * 337 + j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int tmp_sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      int tmp_src[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int tmp_dst[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int k;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_src[k] = orig[(i - 1 + 336) * 337 + j - 1 + 336 + k];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_dst[k] = tmp_src[k] + filter[k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_sum += tmp_dst[k];
      }
      sol[i * 337 + j] = tmp_sum;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      inner:
      for (k = -4; k < 5; k++) {
        sum += filter[4 + k] * orig[i * 256 + j + k];
      }
      sol[i * 256 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}