The provided testbench code is also in C and called `test.c`. The testbench code declares two arrays of 8,192 32-bit integers named `orig` and `sol` and a 3x3 filter array named `filter`. The testbench code then calls the `stencil` function, passing in the `orig` array and the `sol` array and the `filter` array. After the call to `stencil`, the content of the `sol` array is checked using assert statements to validate the stencil computation.

#include <stdio.h>
#include <assert.h>
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int batch;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int k_row = i + ((k / 3) - 1);
        int k_col = j + ((k % 3) - 1);
        if ((k_row >= 0) && (k_row < 256) && (k_col >= 0) && (k_col < 256)) {
          int index = k_row * 256 + k_col;
          sum += orig[index] * filter[k];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}
int main()
{
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_array:
  for (int i = 0; i < 8192; i++) {
    orig[i] = i;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil(orig, sol, filter);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  verify:
  for (int i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (int j = 0; j < 256; j++) {
      int idx = i * 256 + j;
      assert(sol[idx] == ((i - 1) * 256 + (j - 1)));
    }
  }
}