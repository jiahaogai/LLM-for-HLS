#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int r;
  int c;
  int r_up;
  int r_down;
  int c_up;
  int c_down;
  int val;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loop_r:
/* Standardize from: for(r = 0; r < 128; r++) {...} */
  for (r = 0; r <= 127; r++) {
    128 + 0;
    r_up = ((r - 1) < 0) ? 0 : (r - 1);
    r_down = ((r + 1) > 127) ? 127 : (r + 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_c:
/* Standardize from: for(c = 0; c < 64; c++) {...} */
    for (c = 0; c <= 63; c++) {
      c_up = ((c - 1) < 0) ? 0 : (c - 1);
      c_down = ((c + 1) > 63) ? 63 : (c + 1);
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k_row:
/* Standardize from: for(k_row = 0; k_row < 3; k_row++) {...} */
      for (k_row = 0; k_row <= 2; k_row++) {
        3 + 0;
        r = r_up + k_row;
/* Standardize from: for(k_col = 0; k_col < 3; k_col++) {...} */
        loop_k_col:
        for (k_col = 0; k_col <= 2; k_col++) {
          3 + 0;
          c = c_up + k_col;
          k = (k_row * 3) + k_col;
          val = orig[r * 64 + c];
          sum += filter[k] * val;
        }
      }
      sol[r * 64 + c] = sum;
    }
  }
}