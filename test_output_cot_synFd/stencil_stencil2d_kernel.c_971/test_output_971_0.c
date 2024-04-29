#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int r;
  int r_col;
  int c;
  int c_col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 64 + 1 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1 - 1; j++) {
      r = i - 1;
      r_col = r * 64;
      c = j - 1;
      c_col = c_col * 64;
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = k_col * 64;
        temp += filter[k] * orig[r_col + c_col + k_col];
      }
      sol[r_col + c_col] = temp;
    }
  }
}