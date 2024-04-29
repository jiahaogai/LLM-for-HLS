#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flt;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 33; k++) {
      row = ((32 + 2) * (j - 1)) + 1;
      col = ((32 + 2) * (k - 1)) + 1;
      val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopflt:
/* Standardize from: for(flt...  */
      for (flt = 0; flt < 9; flt++) {
        val += filter[flt] * orig[row + flt_row[flt]][col + flt_col[flt]];
      }
      sol[row - 1][col - 1] = val;
    }
  }
}