#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{11}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      k = 8190 - j + k_col;
      if (k < 0) {
        k = -k;
      }
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{11}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        int _k = k + (8190 - 8199 + 1) * k_row;
        if (_k < 8192 && _k >= 0) {
          sum += filter[k_row] * orig[_k];
        }
      }
      sol[j] = sum;
    }
  }
}