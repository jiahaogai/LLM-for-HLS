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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = (i - 4 + 8192) % 8192;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      while (k_col < 9) {
        k = (k_col + 8192) % 8192;
        sum = ((double )0);
        math:
        for (k_col = 0; k_col < 9; k_col++) {
          sum += filter[k_col] * orig[k * 8192 + i_col];
        }
        sol[k * 8192 + j] = sum;
      }
    }
  }
}