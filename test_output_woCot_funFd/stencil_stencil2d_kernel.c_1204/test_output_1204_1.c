the appropriate element in the `sol` array.

---

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128 + 2 * pad; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2 * pad; j++) {
      i_col = i - 1 - pad;
      int orig_row_col_pad[3];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner_pad:
      for (k_col = 0; k_col < 3; k_col++) {
        int orig_row_col;
        if (i_col < 0 || i_col > 127) {
          orig_row_col = 0;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner:
        for (k = 0; k < 3; k++) {
          int orig_index = i_col * 64 + j - 1 - pad + k * 64;
          if (orig_index < 0 || orig_index > 8191) {
            orig_row_col = 0;
          }
          else {
            orig_row_col = orig[orig_index];
          }
          orig_row_col_pad[k_col] = orig_row_col;
        }
        i_col += 1;
      }
      int sol_row_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int k1;
      inner1:
      for (k1 = 0; k1 < 3; k1++) {
        int k2;
        int temp = 0;
        int filter_row_col = filter[k1 * 3 + k2];
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{2}
        inner2:
        for (k2 = 0; k2 < 3; k2++) {
          temp += orig_row_col_pad[k2] * filter_row_col;
        }
        sol_row_col += temp;
      }
      sol[i * 64 + j - 1 - pad] = sol_row_col;
    }
  }
}