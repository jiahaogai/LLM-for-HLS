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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      middle:
      for (k = -4; k < 5; k++) {
        k_col = i + k;
        if (k_col < 0) {
          k_col = 0;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        inner_middle:
        for (i_col = -4; i_col < 5; i_col++) {
          int i_col_orig = i_col + ((4 - 1) + 0);
          int k_col_orig = k_col + ((4 - 1) + 0);
          if (((i_col_orig >= 0) && (i_col_orig < 8192))) {
            if (((k_col_orig >= 0) && (k_col_orig < 8192))) {
              sum += (filter[(((k + 4) * 4) + (i_col + 4))]) * orig[k_col_orig * 8192 + i_col_orig];
            }
          }
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}