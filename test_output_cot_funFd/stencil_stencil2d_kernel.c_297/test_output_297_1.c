Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int orig_row;
  int orig_col;
  int filter_elem;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      orig_row = i - 1;
      orig_col = j - 1;
      sum = 0;
      
      inner:
      for (k_row = 0; k_row < 9; k_row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_middle:
        for (k_col = 0; k_col < 9; k_col++) {
          k = k_row * 9 + k_col;
          filter_elem = filter[k];
          orig_index = orig_row + k_row - 4 + ((orig_col + k_col - 4) * 128);
          sum += orig[orig_index] * filter_elem;
        }
      }
      sol[i * (64 + 2) + j] = sum;
    }
  }
}