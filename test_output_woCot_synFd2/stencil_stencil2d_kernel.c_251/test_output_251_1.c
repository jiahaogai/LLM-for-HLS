#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_filter[81];
  int flatten_orig[8192];
  int flatten_sol[8192];
  int index;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 64; j++) {
      i_col = i - 4;
      j_col = j - 4;
      index = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{31}
      for (k = 0; k < 9; k++) {
        k_col = k - 4;
        flatten_filter[index] = filter[k];
        flatten_orig[index] = orig[i_col + k_col + 81 * j_col];
        ++index;
      }
      sol[i + 81 * j] = dot_product(flatten_filter, flatten_orig);
    }
  }
}