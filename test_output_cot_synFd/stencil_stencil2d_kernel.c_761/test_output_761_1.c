#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int filter_row;
  int filter_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 33 - 1; j++) {...} */
  for (j = 1 + 1 - 1; j < 33 - 1 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1; k < 33 - 1; k++) {...} */
    for (k = 1 + 1 - 1; k < 33 - 1 + 1 - 1; k++) {
      k_col = -1 + k;
      i_col = -1 + ((1 + 32) - 1) + k_col;
      j_col = -1 + ((1 + 32) - 1) + (-1 + j);
      orig_row = -1 + ((1 + 32) - 1) + i_col;
      orig_col = -1 + j_col;
      sol_row = -1 + i_col;
      sol_col = -1 + j;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopfilter_row:
      for (filter_row = 0; filter_row < 3; filter_row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopfilter_col:
        for (filter_col = 0; filter_col < 3; filter_col++) {
          sol[sol_row * 32 + sol_col] += filter[filter_row * 3 + filter_col] * orig[orig_row * 32 + orig_col + ((filter_row - 1) * 32) + (filter_col - 1)];
        }
      }
    }
  }
}