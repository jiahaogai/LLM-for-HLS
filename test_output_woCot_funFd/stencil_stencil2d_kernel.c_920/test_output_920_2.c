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
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 0; c < 32; c++) {
      double sum = 0.0;
      int r_low = r - fl;
      int r_high = r + fl;
      int c_low = c - fl;
      int c_high = c + fl;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (i = r_low; i < r_high; i++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
        for (int j = c_low; j < c_high; j++) {
          int ij = i * 32 + j;
          sum += orig[ij] * filter[i * 32 + j];
        }
      }
      sol[r * 32 + c] = sum;
    }
  }
}