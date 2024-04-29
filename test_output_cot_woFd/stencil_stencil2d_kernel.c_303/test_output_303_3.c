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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j - 4 + k_col;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk:
      for (k = 0; k < 9; k++) {
        i = i_col + k - 4;
        sum += filter[k] * orig[i];
      }
      sol[j] = sum;
    }
  }
}