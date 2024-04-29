#pragma ACCEL kernel

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
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_stencil:
/* Standardize from: for(j = 1; j < 33 - 1; j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_stencil:
/* Standardize from: for(i = 1; i < 32 - 1; i++) {...} */
    for (i = 1 + 0; i < 32 - 1 + 0; i++) {
      orig_row = 32 * (j - 1);
      sol_row = 32 * (j - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_stencil:
/* Standardize from: for(k = 0; k < 9; k++) {...} */
      for (k = 0; k < 9; k++) {
        orig_col = i * 32;
        sol_col = i * 32;
        filter_elem = filter[k];
        i_col = orig_col + 1 + (k % 3);
        j_col = orig_row + 1 + (k / 3);
        sol[sol_col + j_col] += filter_elem * orig[i_col + j_col];
      }
    }
  }
}