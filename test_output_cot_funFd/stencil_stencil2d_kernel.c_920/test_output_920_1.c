#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[256])
{
  int r;
  int c;
  int i;
  int fl = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (c = 1; c < 33; c++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 256; i++) {
        int r_tmp = r + (-16 + ((i >> 6) & 31));
        int c_tmp = c + (-16 + (i & 31));
        if ((r_tmp >= 0) && (r_tmp < 32) && (c_tmp >= 0) && (c_tmp < 32)) {
          int r_idx = r_tmp << 5;
          int c_idx = c_tmp << 5;
          double in = orig[r_idx + c_idx];
          double f = filter[i];
          sum += in * f;
        }
      }
      sol[r << 5 | c] = sum;
    }
  }
}