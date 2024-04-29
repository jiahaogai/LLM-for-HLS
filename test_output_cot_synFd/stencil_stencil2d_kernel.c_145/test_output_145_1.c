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
  for (r = 2; r <= 128 + 2 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 2; c <= 64 + 2 - 1; c++) {
      i = r - 2;
      j = c - 2;
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loop_k1:
      for (k = 0; k < 9; ++k) {
        k_col = k - 4;
        i_col = i + k_col;
        j_col = j;
        sum += filter[k] * orig[i_col * 64 + j_col];
      }
      sol[i * 64 + j] = sum;
    }
  }
}