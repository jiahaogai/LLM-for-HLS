#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int filter_elem;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      j_col = j - 4;
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k - 4;
        filter_elem = filter[k];
        int orig_idx = i_col + k_col;
        int sol_idx = j_col + k_col;
        if ((((orig_idx >= 0) && (orig_idx < 256))) && (((sol_idx >= 0) && (sol_idx < 256)))) {
          sum += filter_elem * orig[orig_idx * 256 + sol_idx];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}