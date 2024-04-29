#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int r_up;
  int r_down;
  int c_up;
  int c_down;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 1; r < 128 + 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 64 + 1; c++) {
      r_up = r - 1;
      r_down = r + 1;
      c_up = c - 1;
      c_down = c + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        for (j = 0; j < 3; j++) {
          i = k * 32 + j;
          t += filter[i] * orig[r_up * 64 + c_up * 32 + i];
        }
      }
      sol[r * 64 + c * 32] = t;
    }
  }
}