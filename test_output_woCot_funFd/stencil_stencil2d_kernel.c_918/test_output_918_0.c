#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_index;
  int value;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_stencil_1:
/* Standardize from: for(i = 0; i < 32; i++) {...} */
  for (i = 0; i <= 31; i += 32) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_stencil_2:
/* Standardize from: for(j = 0; j < 32; j++) {...} */
    for (j = 0; j <= 31; j += 32) {
      i_col = i;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_stencil_3:
/* Standardize from: for(k = 0; k < 9; k++) {...} */
      for (k = 0; k < 9; k++) {
        k_col = k - 4 + i;
        j_col = j - 4 + j;
        flatten_index = (32 + 8) * k_col + j_col;
        value = filter[k] * orig[flatten_index];
        sol[flatten_index] = value;
      }
    }
  }
}