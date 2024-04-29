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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  loopj:
/* Standardize from: for(j = 1;j < 8191;j++) {...} */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk_row:
      for (k_row = 0 - 4; k_row <= 4 - 1; k_row++) {
        i = k_row + j;
        if (i < 0 || i > 8191) {
          continue;
        }
        sum += filter[k_col] * orig[i * 8192 + k_col];
      }
      sol[j * 8192 + k_col] = sum;
    }
  }
}