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
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 0; c < 64; c++) {
      temp = 0;
      mul = 1;
      k1 = r - 1;
      if (k1 < 0) {
        k1 = 0;
      }
      
#pragma ACCEL PARALLEL reduction{temp}
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = k1; k <= r + 1; k++) {
        k2 = c - 1;
        if (k2 < 0) {
          k2 = 0;
        }
        
#pragma ACCEL PARALLEL reduction{temp}
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        for (k = k2; k <= c + 1; k++) {
          mul *= filter[k - k2];
          temp += orig[k + 64L * k1] * mul;
        }
        mul = 1;
      }
      sol[r + 64L * c] = temp;
    }
  }
}