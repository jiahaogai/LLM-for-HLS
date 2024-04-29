#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (i_col + ((k % 3) - 1) < 0 || i_col + ((k % 3) - 1) > 255) {
          k_col = 0;
        }
         else {
          k_col = i_col + ((k % 3) - 1);
        }
        j_col = j - 4 + (k - (k % 3));
        if (j_col < 0 || j_col > 255) {
          continue;
        }
        sol[i * 256 + j] += orig[k_col * 256 + j_col] * filter[k];
      }
    }
  }
}