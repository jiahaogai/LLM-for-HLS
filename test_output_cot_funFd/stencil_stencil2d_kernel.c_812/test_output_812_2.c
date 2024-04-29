#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_i:
      for (k_col = 0; k_col < 9; k_col++) {
        if (i_col + k_col + 4 < 0 || i_col + k_col + 4 > 255) {
          continue;
        }
        j_col = j - 4;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_j:
        for (k = 0; k < 9; k++) {
          if (j_col + k + 4 < 0 || j_col + k + 4 > 255) {
            continue;
          }
          flatten_i = i_col + k_col;
          flatten_j = j_col + k;
          sol[i * 256 + j] += orig[flatten_i * 256 + flatten_j] * filter[k];
        }
      }
    }
  }
}