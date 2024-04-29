#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int r;
  int c;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 256; r < 8192 - 256; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 256; c < 8192 - 256; c++) {
      temp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        temp += filter[k] * orig[r + (-1 + k_col) * 64 + c + (-1 + (k - k_col)) * 64];
      }
      sol[r * 64 + c] = temp;
    }
  }
}