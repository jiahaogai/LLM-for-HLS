#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int k;
  int r_col;
  int c_col;
  double mul;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (c = 0; c < 64 + 2; c++) {
      temp = 0.0;
      r_col = r - 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (c_col = c - 1; c_col <= c + 1; c_col++) {
        mul = filter[((c_col - c) + 4)] * orig[r_col * (64 + 2) + c_col];
        temp += mul;
      }
      sol[r * (64 + 2) + c] = temp;
    }
  }
}