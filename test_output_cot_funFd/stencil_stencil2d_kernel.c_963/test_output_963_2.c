#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int r_up;
  int r_down;
  int c_left;
  int c_right;
  int t;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
/* Standardize from: for(r = 1;r < 8192 - 1;r++) {...} */
  for (r = 1 + 0; r <= 8192 + 1 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
/* Standardize from: for(c = 1;c < 8192 - 1;c++) {...} */
    for (c = 1 + 0; c <= 8192 + 1 - 1; c++) {
      r_up = r - 1;
      r_down = r + 1;
      c_left = c - 1;
      c_right = c + 1;
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loop_t:
      for (t = 0; t < 9; t++) {
        sum += filter[t] * orig[r_up * 8192 + c_left + t - 4];
      }
      sol[r * 8192 + c] = sum;
    }
  }
}