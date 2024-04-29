#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j <= 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      k = j - 4 + k_col;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        int _k = k + 1;
        if (_k < 1) {
          _k = 1;
        }
        if (_k > 8191) {
          _k = 8191;
        }
        sum += filter[k_row] * orig[_k];
      }
      sol[j] = sum;
    }
  }
}