#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 16
#define M 16
#define FILTER_SIZE 9

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int idx = 0;
  
#pragma scop
  
#pragma no_pipeline
  
#pragma no_app
  for (i = 0; i < 16; i++) {
    
#pragma no_app
    for (j = 0; j < 16; j++) {
      i_col = i - 4;
      
#pragma no_app
      while (i_col < 0) {
        i_col += 1;
        idx++;
      }
      
#pragma no_app
      j_col = j - 4;
      
#pragma no_app
      while (j_col < 0) {
        j_col += 1;
        idx++;
      }
      
#pragma no_app
      k_col = 0;
      
#pragma no_app
      while (k_col < 9) {
        k = k_col + idx;
        sol[k] = ((filter[k_col]) * orig[k]);
        k_col++;
      }
      
#pragma no_app
      idx += 16 - 1;
    }
  }
  
#pragma endscop
}