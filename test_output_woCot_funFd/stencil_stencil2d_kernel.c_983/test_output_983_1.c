#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      sol[i * 256 + j] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 + (-4 + k))) * 256;
        i_col = i * 256;
        j_col = (8 + (-4 + k)) * 1;
        filter_elem = filter[k];
        sol[i * 256 + j] += orig[i_col + k_col] * filter_elem * orig[j_col];
      }
    }
  }
}