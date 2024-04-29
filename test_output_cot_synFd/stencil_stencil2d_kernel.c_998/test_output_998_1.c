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
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 1; c < 8191; c++) {
      sol[r * 8192 + c] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        k_col = k / 3;
        r_col = r + (-1 + k_col);
        sol[r * 8192 + c] += filter[k] * orig[r_col * 8192 + c];
      }
    }
  }
}