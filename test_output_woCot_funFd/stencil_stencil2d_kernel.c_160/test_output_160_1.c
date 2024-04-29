Code: 
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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 - 1;j++) {...} */
  for (j = 1 + 0; j < 32 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      i_col = 0 + k_col;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk:
      for (k = 1; k < 32 + 1 - 1; k++) {
        i = k + i_col;
        sum += filter[k - 1] * orig[i];
      }
      sol[i_col] = sum;
    }
  }
}