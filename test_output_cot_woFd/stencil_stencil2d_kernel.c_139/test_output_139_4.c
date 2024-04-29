#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k1;
  int k2;
  double mul;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 0; c < 64 + 2; c++) {
      temp = 0.0;
      k1 = r - 1;
      k2 = c - 1;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 9; i++) {
        mul = filter[i] * orig[k1 + i * 128][k2];
        temp += mul;
      }
      sol[r * (64 + 2) + c] = temp;
    }
  }
}