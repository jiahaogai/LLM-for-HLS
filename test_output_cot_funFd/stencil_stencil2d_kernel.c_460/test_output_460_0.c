#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{16}
      inner_i:
      for (k_col = 0; k_col < 9; k_col++) {
        if (i_col + k_col < 0 || i_col + k_col >= 256) {
          continue;
        }
        j_col = j - 4;
        
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{16}
        inner_j:
        for (k = 0; k < 9; k++) {
          if (j_col + k < 0 || j_col + k >= 256) {
            continue;
          }
          sol[i * 256 + j] += filter[k_col * 9 + k] * orig[i_col * 256 + j_col + k];
        }
      }
    }
  }
}