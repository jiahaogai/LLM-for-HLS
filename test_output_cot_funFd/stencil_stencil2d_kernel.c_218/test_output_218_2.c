#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int r_col;
  int c_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 1; c < 8191; c++) {
      r_col = r - 4;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      for (i = 0; i < 5; i++) {
        c_col = c - 4;
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{32}
        for (j = 0; j < 5; j++) {
          sol[r * 8192 + c] += filter[i * 5 + j] * orig[r_col * 8192 + c_col + j];
        }
        c_col = c + 1;
      }
      r_col = r + 1;
    }
  }
}