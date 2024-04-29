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
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 256; i++) {
        int r_tmp = r + ((int )filter[i]) / 2;
        int c_tmp = c + ((int )filter[i]) / 2;
        if (r_tmp < 1 || r_tmp > 8191) {
          r_tmp = 1;
        }
        if (c_tmp < 1 || c_tmp > 8191) {
          c_tmp = 1;
        }
        sum += ((double )orig[r_tmp * 8192 + c_tmp]) * filter[i];
      }
      sol[r * 8192 + c] = sum;
    }
  }
}