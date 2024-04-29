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
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 0 + 1; j < 33 + 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      int _in_k_col = 0 + k_col;
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      loopi_col:
      for (i_col = 0; i_col < 32; i_col++) {
        int _in_i_col = 0 + i_col;
        sum += filter[k_col] * orig[i_col + (_in_j - 1) * 32 + (_in_k_col - 1) * 32 * 33];
      }
      sol[j + k_col * 33] = sum;
    }
  }
}