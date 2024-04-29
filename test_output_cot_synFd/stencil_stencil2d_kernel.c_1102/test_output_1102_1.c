# pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{7}
void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 1; k_col < 32 + 1 - 1; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 1; k_row < 32 + 1 - 1; k_row++) {
        k = k_row * (32 + 1) + k_col;
        sum += filter[k] * orig[k];
      }
      sol[j * (32 + 1) + k_col] = sum;
    }
  }
}