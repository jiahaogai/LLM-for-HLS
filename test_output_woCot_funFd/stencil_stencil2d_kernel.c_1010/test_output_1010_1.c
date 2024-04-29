from each element in the input array the corresponding element in the output array by applying the following formula:


sol[index] = filter[0] * orig[index] + 
             filter[1] * (orig[index + 1] + orig[index - 1]) +
             filter[2] * orig[index + 2] + ... +
             filter[8] * orig[index + 8]


where each `orig[index_i]` is a pixel in the input 2D array, filter[i] are the coefficients in the filter kernel and the sum is taken over the `i`th index of the kernel. Note that the `orig` input and the `sol` output can point to the same array with no additional allocation.

 

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 337; j++) {
      index = i * 337 + j;
      sol[index] = ((filter[0] * orig[index]) + (filter[1] * (orig[index + 1] + orig[index - 1])) + (filter[2] * orig[index + 2]) + (filter[3] * (orig[index + 3] + orig[index - 3])) + (filter[4] * orig[index + 4]) + (filter[5] * (orig[index + 5] + orig[index - 5])) + (filter[6] * orig[index + 6]) + (filter[7] * (orig[index + 7] + orig[index - 7])) + (filter[8] * orig[index + 8])) / 256;
    }
  }
}