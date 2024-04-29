#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j <= 8191; j++) {
    int _in_j = 8191;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      int _in_k_col = 8191;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 9; i_col++) {
        int _in_i_col = 8191;
        sum = 0.0;
        int _in_k = 8191;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        loopk:
        for (k = -4; k <= 4; k++) {
          int _in_k = 8191;
          int _in_i = 8191;
          sum += filter[k + 4] * orig[(_in_k * 64) + (_in_i * 8)];
        }
        sol[(_in_k_col * 64) + (_in_i_col * 8)] = sum;
      }
    }
  }
}