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
  int r_col_start;
  int r_col_end;
  int c_col_start;
  int c_col_end;
  int k1;
  int k2;
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  r_col_start = 1;
  r_col_end = 128 + 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  c_col_start = 1;
  c_col_end = 128 + 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{off}
    for (c = 0; c < 128 + 2; c++) {
      i_col = r - 1;
      j_col = c - 1;
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = k - 1;
        temp += filter[k] * orig[i_col * 128 + j_col + k_col];
      }
      sol[r * 128 + c] = temp;
    }
  }
}