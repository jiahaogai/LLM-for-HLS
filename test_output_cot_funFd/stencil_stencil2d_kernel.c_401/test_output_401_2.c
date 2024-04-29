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
  int c_left;
  int c_right;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 2; c < 64 - 2; c++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j = 0; j < 3; j++) {
          r_up = r - 2 + k;
          c_left = c - 2 + j;
          t += filter[k * 3 + j] * orig[r_up * 64 + c_left];
        }
      }
      sol[r * 64 + c] = t;
    }
  }
}