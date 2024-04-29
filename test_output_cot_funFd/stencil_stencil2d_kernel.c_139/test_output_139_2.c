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
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 0; c < 64; c++) {
      temp = 0;
      mul = 1;
      k1 = r - 1;
      if (k1 < 0) {
        k1 = 0;
      }
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{16}
      for (k = k1; k < 128 + 1; k++) {
        k2 = c - 1;
        if (k2 < 0) {
          k2 = 0;
        }
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{16}
        for (k = k2; k < 64 + 1; k++) {
          temp += mul * orig[k * 128 + r];
          mul *= filter[8];
        }
        mul = 1;
      }
      sol[r * 64 + c] = temp;
    }
  }
}