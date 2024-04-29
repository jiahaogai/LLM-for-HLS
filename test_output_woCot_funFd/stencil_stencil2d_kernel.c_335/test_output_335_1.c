Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int filter_row;
  int filter_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 256;
      sol_row = i * 256;
      
      inner:
      for (k = 0; k < 256; k += 8) {
        orig_col = k + orig_row;
        sol_col = k + sol_row;
        int sum = 0;
        
        int k_col_bound = ((k + 8) < 256) ? 8 : 256 - k;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        inner_par:
        for (k_col = 0; k_col < k_col_bound; k_col++) {
          int i_col = k_col + orig_col;
          int filter_col = k_col * 256;
          int v = orig[i_col] * filter[filter_col];
          sum += v;
        }
        sol[sol_col] = sum;
      }
    }
  }
}