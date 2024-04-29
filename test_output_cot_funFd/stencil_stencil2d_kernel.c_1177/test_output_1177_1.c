#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{9}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      loopk_col:
      for (k_col = -4; k_col <= 4; k_col++) {
        i_col = i + k_col;
        if ((((i_col >= 1) && (i_col <= 8192))) && ((j >= 1) && (j <= 8192))) {
          sum += filter[4 + k_col] * orig[i_col + (j - 1) * 8192];
        }
      }
      sol[i + j * 8192] = sum;
    }
  }
}