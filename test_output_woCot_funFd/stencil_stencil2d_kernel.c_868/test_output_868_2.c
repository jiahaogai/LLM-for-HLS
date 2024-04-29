Code: #pragma ACCEL kernel

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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 0;j < 129;j++) {...} */
  for (j = 0; j <= 128; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j - 4 + k_col;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopi:
      for (i = 0; i < 8; i++) {
        i_col_tmp = i_col + i;
        if ((((0 <= i_col_tmp) && (i_col_tmp < 129))) && ((j > 3) && (j < 127))) {
          sum += filter[k_col] * orig[i_col_tmp];
        }
      }
      sol[j] = sum;
    }
  }
}