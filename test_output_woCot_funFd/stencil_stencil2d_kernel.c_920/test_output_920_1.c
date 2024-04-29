#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[256])
{
  int r;
  int c;
  int i;
  int fl = 256 / 2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 0; r < 32; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 0; c < 32; c++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 256; i++) {
        int orig_r = r + (i - fl);
        int orig_c = c + (i - fl);
        if (orig_r < 0 || orig_r > 31 || orig_c < 0 || orig_c > 31) {
          continue;
        }
        else {
          sum += filter[i] * orig[orig_r * 32 + orig_c];
        }
      }
      sol[r * 32 + c] = sum;
    }
  }
}