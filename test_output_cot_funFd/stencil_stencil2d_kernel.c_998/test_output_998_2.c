#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k;
  int k_col;
  int r_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (c = 1; c < 8191; c++) {
      sol[r * 8192 + c] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (k = 0; k < 9; k++) {
        k_col = (8191 + k - r) % 8191;
        r_col = (8191 + k_col - c) % 8191;
        sol[r * 8192 + c] += filter[k] * orig[r_col * 8192 + c_col];
      }
    }
  }
}