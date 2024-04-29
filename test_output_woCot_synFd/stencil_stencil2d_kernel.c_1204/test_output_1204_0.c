***

 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int row;
  int col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 0;j < 64;j++) {...} */
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 0;k_col < 3;k_col++) {...} */
    for (k_col = 0; k_col < 3; k_col++) {
      i_col = j + (-1 + k_col);
      
#pragma ACCEL PARALLEL reduction = temp FACTOR=auto{1}
      loopk:
/* Standardize from: for(k = 0;k < 3;k++) {...} */
      for (k = 0; k < 3; k++) {
        int _in_orig[1];
        int _in_sol[1];
        int _out_sol[1];
        _in_orig[0] = orig[i_col + (32 * k)];
        _in_sol[0] = sol[i_col + (32 * k)];
        _out_sol[0] = _in_sol[0] + filter[k] * _in_orig[0];
        sol[_in_orig[0]] = _out_sol[0];
      }
    }
  }
}