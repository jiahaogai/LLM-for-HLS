#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 8; j < 8184; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 1; k_col < 9; k_col++) {
      i_col = j - 8 + k_col;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk:
/* Standardize from: for(k ... ) */
      for (k = 0; k < 9; k++) {
        i = i_col - 4 + k;
        sum += filter[k] * orig[i];
      }
      sol[j] = sum;
    }
  }
}