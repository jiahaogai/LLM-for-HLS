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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = -4; k <= 4; k++) {
        k_col = k + 4;
        i_col = i + k_col;
        if ((((i_col >= 1) && (i_col <= 8192))) && ((j >= 1) && (j <= 8192))) {
          sum += filter[k + 4] * orig[i_col - 1];
        }
      }
      sol[j - 1] = sum;
    }
  }
}