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
  int r_col;
  int c;
  int buf;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
/* Standardize from: for(r = 1;r < 8;r++) {...} */
  for (r = 1; r < 8; r++) {
     r_col = 8 * r;
     loop_c:
/* Standardize from: for(c = 1;c < 8;c++) {...} */
    for (c = 1; c < 8; c++) {
      i_col = r_col + c;
      sum = 0.0;
      loop_k:
/* Standardize from: for(k = 0;k < 9;k++) {...} */
      for (k = 0; k < 9; k++) {
        j_col = r_col + k - 4;
        buf = orig[i_col] * filter[k] + sol[j_col] * filter[k];
        sum += buf;
      }
      sol[i_col] = sum;
    }
  }
}