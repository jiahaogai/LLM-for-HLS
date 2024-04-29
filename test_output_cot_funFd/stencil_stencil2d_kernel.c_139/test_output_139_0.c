#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 0; c < 64 + 2; c++) {
      double temp = 0.0;
      int k_col;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        k_col = k + (r - 1);
        temp += filter[k] * orig[k_col * (64 + 2) + c - 1];
      }
      sol[r * (64 + 2) + c] = temp;
    }
  }
//#pragma endscop
}