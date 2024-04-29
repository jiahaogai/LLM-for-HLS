Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      orig_row = 33 * (j - 1);
      orig_col = 33 * (i - 1);
      sol_row = 33 * (j - 1);
      sol_col = 33 * (i - 1);
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        k_col = (k % 3) + orig_col;
        i_col = ((k - 1) / 3) + orig_row;
        j_col = i_col;
        sum += filter[k] * orig[i_col * 33 + k_col];
      }
      sol[sol_row * 32 + sol_col] = sum;
    }
  }
}