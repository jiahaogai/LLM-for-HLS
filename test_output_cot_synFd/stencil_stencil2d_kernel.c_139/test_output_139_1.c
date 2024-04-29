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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 0; c < 64 + 2; c++) {
      temp = 0;
      mul = 1;
      k1 = r - 1;
      k2 = c - 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        if ((k1 < 0) || (k1 > 127) || (k2 < 0) || (k2 > 63)) {
          mul = 0;
        }
        temp += mul * filter[k] * orig[k1 * 64 + k2];
        k1 += 1;
        k2 += 1;
      }
      sol[r * 64 + c] = temp;
    }
  }
}