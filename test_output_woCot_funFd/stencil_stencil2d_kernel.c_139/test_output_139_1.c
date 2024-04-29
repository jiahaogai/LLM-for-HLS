Code: 
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
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 256; r < 128 + 256; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 256; c < 64 + 256; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        r_col = r - 4 + k / 3;
        c_col = c - 4 + k % 3;
        if (r_col >= 0 && r_col < 128 && c_col >= 0 && c_col < 64) {
          k_col = r_col * 64 + c_col;
          temp += mul * orig[k_col] * filter[k];
        }
        mul *= -1;
      }
      sol[r * 64 + c] = temp;
    }
  }
}