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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (jj = -1 * pad; jj <= 1 * pad; jj++) {
          t += filter[((k + 1) * 3) + (jj + 1)] * orig[i * 64 + (j * 8 + k) * 8 + jj];
        }
      }
      sol[i * 64 + j * 8] = t;
    }
  }
}