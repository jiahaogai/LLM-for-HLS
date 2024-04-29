#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k;
  int k1;
  int k2;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 256; r < 128 + 256; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 256; c < 64 + 256; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k1 = r - 4 + k / 3;
        k2 = c - 4 + k % 3;
        temp += mul * orig[k1 * 64 + k2];
        mul *= filter[k];
      }
      sol[r * 64 + c] = temp;
    }
  }
}