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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner:
      while (k_col < 9) {
        int tmp_k_col = k_col;
        k_col++;
        int tmp_i_col = i_col + tmp_k_col;
        if (((0 <= tmp_i_col) && (tmp_i_col < 8192))) {
          int tmp_k = k_col - 4;
          k = tmp_k;
          if (((0 <= k) && (k < 9))) {
            sum += filter[tmp_k] * orig[tmp_i_col * 8192 + k];
          }
        }
      }
      sol[i * 8192 + j] = sum;
      sum = 0.0;
    }
  }
}