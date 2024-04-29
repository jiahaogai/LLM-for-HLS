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
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 2; c < 64 - 2; c++) {
      temp = 0.0;
      r_col = r - 2;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        c_col = c - 2;
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{2}
        for (j = 0; j < 3; j++) {
          temp += filter[i * 3 + j] * orig[r_col * 64 + c_col++];
        }
        r_col++;
      }
      sol[r * 64 + c] = temp;
    }
  }
}