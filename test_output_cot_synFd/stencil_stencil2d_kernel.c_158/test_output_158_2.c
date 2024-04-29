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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 0 + 1; j <= 8192 - 1 + 1 - 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      int _in_k_col = 0 + k_col;
      double _in = orig[_in_j * 8192 + _in_k_col];
      sum += _in * filter[k_col];
    }
    int _out = sum;
    sol[_in_j * 8192] = _out;
    loopi_col:
    for (i_col = 1; i_col < 8192 - 1; i_col++) {
      int _in_i_col = i_col + 1;
      sum = sum - orig[_in_j * 8192 + _in_i_col - 1] + orig[_in_j * 8192 + _in_i_col + 8191];
      _out = sum;
      sol[_in_j * 8192 + _in_i_col] = _out;
    }
    sum = 0.0;
    sum += -orig[_in_j * 8192] + orig[_in_j * 8192 + 8191];
    _out = sum;
    sol[_in_j * 8192 + 8192 - 1] = _out;
  }
}