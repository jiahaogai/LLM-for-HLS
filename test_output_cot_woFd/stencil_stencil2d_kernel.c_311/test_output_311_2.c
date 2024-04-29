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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8192 - 1; i++) {
      sum = 0.0;
      loopk_col:
      for (k_col = 0; k_col < 9; k_col++) {
        i_col = i - 4 + k_col;
        sum += filter[k_col] * orig[i_col];
      }
      sol[j] = sum;
      i++;
    }
    j++;
  }
}