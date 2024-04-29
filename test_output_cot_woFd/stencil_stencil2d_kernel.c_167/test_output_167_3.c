#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 0 + 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 32 + 1; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 32 + 1; i_col++) {
        i = i_col + (j - 1);
        k = k_col;
        sum += orig[i * (32 + 1) + k] * filter[k];
      }
      sol[j * (32 + 1) + k_col] = sum;
    }
  }
}