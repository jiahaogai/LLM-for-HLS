from each element `orig[i][j]` a sum over some of its neighbors as specified by the filter kernel. The parameters are:
  - `orig`: input array
  - `sol`: output array
  - `filter`: filter kernel with size 9
Requirements:
  - `orig` and `sol` are 2D arrays with a total size of 8192
  - `filter` is a 1D array with a size of 9

#pragma once
#include <stdint.h>
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma scop
  
#pragma claw scope(orig)
  
#pragma claw scope(sol)
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma claw scope(filter)
    for (j = 1; j < 32 + 1 - 1; j++) {
      sum = 0;
      
#pragma claw indent(off)
      
#pragma claw scope(orig)
      for (k = -1; k <= 1; k++) {
        
#pragma claw scope(filter)
        sum += orig[i + k][j - 1] * filter[0 + k + 1];
      }
      
#pragma claw scope(orig)
      for (k = -1; k <= 1; k++) {
        
#pragma claw scope(filter)
        sum += orig[i + k][j + 1] * filter[8 + k + 1];
      }
      
#pragma claw scope(filter)
      sol[i][j] = sum;
    }
  }
  
#pragma endscop
}