#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int r;
  int c;
  int r_col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 1; r < 64 - 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 64 - 1; c++) {
      temp = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        r_col = r - 1 + (k - k_col) / 3;
        temp += filter[k] * orig[r_col * 64 + c - 1 + k_col];
      }
      sol[r * 64 + c] = temp;
    }
  }
}