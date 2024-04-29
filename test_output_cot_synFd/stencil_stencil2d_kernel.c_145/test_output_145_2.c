#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int r;
  int c;
  int r_col_s;
  int r_col_e;
  int c_col_s;
  int c_col_e;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
/* Standardize from: for(r = 0; r < 128 + 2; r++) {...} */
  for (r = 0; r <= 128 + 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_c:
/* Standardize from: for(c = 0; c < 64 + 2; c++) {...} */
    for (c = 0; c <= 64 + 1; c++) {
      i_col = r - 1;
      j_col = c - 1;
      r_col_s = (i_col < 0) ? 0 : i_col;
      r_col_e = (i_col > 128 - 1) ? 128 - 1 : i_col;
      c_col_s = (j_col < 0) ? 0 : j_col;
      c_col_e = (j_col > 64 - 1) ? 64 - 1 : j_col;
      loop_k1:
/* Standardize from: for(k = 0; k < 9; k++) {...} */
      for (k = 0; k < 9; k++) {
        k_col = k - 4;
        if (((r_col_s <= r_col_e) && (c_col_s <= c_col_e)) && (k_col <= 8 - 1) && (k_col >= 0)) {
          sol[r * 64 + c] += filter[k] * orig[r_col_s * 64 + c_col_s + k_col];
        }
      }
    }
  }
}