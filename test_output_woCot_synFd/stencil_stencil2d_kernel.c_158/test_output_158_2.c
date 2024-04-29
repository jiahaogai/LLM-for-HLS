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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 0 + 1; j < 33 + 1 - 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 33;k_col++) {...} */
    for (k_col = 0 + 1; k_col < 33 + 1 - 1; k_col++) {
      int _in_k_col = 0 + 1 + k_col;
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 32;i_col++) {...} */
      for (i_col = 0 + 1; i_col < 32 + 1 - 1; i_col++) {
        int _in_i_col = 0 + 1 + i_col;
        sum += filter[0] * orig[(_in_j - 1) * 32 + _in_i_col - 1] + filter[1] * orig[(_in_j - 1) * 32 + _in_i_col + 0] + filter[2] * orig[(_in_j - 1) * 32 + _in_i_col + 1] + filter[3] * orig[_in_j * 32 + _in_i_col - 1] + filter[4] * orig[_in_j * 32 + _in_i_col + 0] + filter[5] * orig[_in_j * 32 + _in_i_col + 1] + filter[6] * orig[(_in_j + 1) * 32 + _in_i_col - 1] + filter[7] * orig[(_in_j + 1) * 32 + _in_i_col + 0] + filter[8] * orig[(_in_j + 1) * 32 + _in_i_col + 1];
      }
      sol[_in_j * 32 + k_col] = sum;
    }
  }
}