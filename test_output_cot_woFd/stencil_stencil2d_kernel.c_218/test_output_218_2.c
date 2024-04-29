#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int r_col;
  int c_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (c = 1; c < 8191; c++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = -4; i <= 4; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = -4; j <= 4; j++) {
          r_col = r + i;
          c_col = c + j;
          if (r_col < 0) {
            r_col = 0;
          }
          if (r_col > 8191) {
            r_col = 8191;
          }
          if (c_col < 0) {
            c_col = 0;
          }
          if (c_col > 8191) {
            c_col = 8191;
          }
          sum += filter[i + 4] * filter[j + 4] * orig[r_col * 8192 + c_col];
        }
      }
      sol[r * 8192 + c] = sum;
    }
  }
}