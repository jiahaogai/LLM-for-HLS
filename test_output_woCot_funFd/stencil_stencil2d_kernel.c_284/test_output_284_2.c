The `orig` array is the 2D input data to the function. The `sol` array is the 2D output data from the function. The `filter` array is a 1D array of integers representing the 2D filter. The function applies the filter to each element of the `orig` array and stores the result in the corresponding element of the `sol` array.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
    }
  }
}