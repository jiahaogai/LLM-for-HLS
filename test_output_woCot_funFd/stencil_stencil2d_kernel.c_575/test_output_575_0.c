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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k - 4;
        i_col = i + k_col;
        if (((i_col >= 0) && (i_col < 256))) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          inner_middle:
          for (j_col = 0; j_col < 9; j_col++) {
            int tmp;
            k_col = k_col - 4;
            i_col = i_col - 4;
            j_col = j_col - 4;
            if (((i_col >= 0) && (i_col < 256) && (j_col >= 0) && (j_col < 256))) {
              tmp = orig[i_col * 256 + j_col];
            }
             else {
              tmp = 0;
            }
            t += filter[k * 9 + j_col] * tmp;
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}