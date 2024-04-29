5. #pragma ACCEL PARAMETER TYPES=int: Define the parameter types of the 'stencil' function.
6. #pragma ACCEL PARAMETER orig: Pass the 'orig' array to the 'stencil' function.
7. #pragma ACCEL PARAMETER sol: Pass the 'sol' array to the 'stencil' function.
8. #pragma ACCEL PARAMETER filter: Pass the 'filter' array to the 'stencil' function.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (k = 0 - pad; k < 8 + pad; k++) {
        t += filter[pad + k] * orig[i * 8 + j * 8 + k];
      }
      sol[i * 8 + j] = t;
    }
  }
}