#pragma ACCEL PIPELINE auto{off}
 
 #pragma ACCEL TILE FACTOR=auto{1}
 
 #pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 1; k_col < 33; k_col++) {
      col = k_col + 1;
      sol[j * 32 + col] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 1; k < 33; k++) {
        row = k + 1;
        sol[j * 32 + col] += filter[k] * orig[row * 32 + col];
      }
    }
  }
}