#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int elem;
  
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
      i_col = ((i - 1) + -1);
      j_col = ((j - 1) + -1);
      min_i = ((i_col > 0 ? 0 : 1 - i_col) + i_col);
      max_i = ((256 - i_col) + 1);
      min_j = ((j_col > 0 ? 0 : 1 - j_col) + j_col);
      max_j = ((256 - j_col) + 1);
      elem = 0;
      
#pragma ACCEL PARALLEL reduction=elem FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((k - 1) + -1);
        elem += ((orig[(((i + min_i) - 1) + ((j + min_j) - 1)) + k_col] * filter[k]) + 0);
      }
      sol[i + j] = elem;
    }
  }
}