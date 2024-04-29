#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[256])
{
  int r;
  int c;
  int i;
  int fl = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (c = 1; c < 8191; c++) {
      sol[r * 8192 + c] = 0.0;
      fl = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 256; i++) {
        sol[r * 8192 + c] += filter[i] * orig[(r + (-128 + i)) * 8192 + c];
        fl++;
      }
    }
  }
}