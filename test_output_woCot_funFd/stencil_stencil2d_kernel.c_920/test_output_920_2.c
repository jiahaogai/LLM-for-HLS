#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[256])
{
  int r;
  int c;
  int i;
  int fl;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 64 - 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (c = 1; c < 64 - 1; c++) {
      double sum = 0.0;
      int i_col = -1 * (256 / 8);
      int i_row = -1;
      while (i_row < 256) {
        i = i_row * 8 + i_col;
        sum += filter[i] * orig[r * 64 + c - (i_col + 1)];
        i_row += 1;
        i_col = -1;
      }
      sol[r * 64 + c] = sum;
    }
  }
}