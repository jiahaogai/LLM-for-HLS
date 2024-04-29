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
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      inner:
      while (k_col < 9) {
        int cur_i_col = i_col + k_col;
        int cur_k = k_col;
        if (cur_i_col >= 0 && cur_i_col < 8192) {
          sol[i] += orig[cur_i_col] * filter[cur_k];
        }
        ++k_col;
      }
      sum = sol[i];
      if (sum > 0.0) {
        sol[i] = sum;
      }
      else {
        sol[i] = 0.0;
      }
    }
  }
}