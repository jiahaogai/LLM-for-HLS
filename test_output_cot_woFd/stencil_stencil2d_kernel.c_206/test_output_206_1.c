#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int r_col;
  int c_col;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 2; r < 128 - 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (c = 2; c < 64 - 1; c++) {
      r_col = r - 1;
      c_col = c - 1;
      temp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = 0; j < 3; j++) {
          temp += filter[i * 3 + j] * orig[r_col + i][c_col + j];
        }
      }
      sol[r][c] = temp;
    }
  }
}