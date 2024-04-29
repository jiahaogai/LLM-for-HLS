#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int r;
  int r_up;
  int r_down;
  int c;
  int c_left;
  int c_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 1; c < 33; c++) {
      r_up = r - 1;
      r_down = r + 1;
      c_left = c - 1;
      c_right = c + 1;
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = r_up + ((0 <= r_up) ? 0 : -r_up);
        j = c_left + ((0 <= c_left) ? 0 : -c_left);
        sum += filter[k] * orig[i * 32 + j];
      }
      sol[r * 32 + c] = sum;
    }
  }
}