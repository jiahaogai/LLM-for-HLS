#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int range_l;
  int range_r;
  int idx_orig;
  int idx_sol;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      idx_orig = i * 64 + j;
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = (k % 3) * 64;
        range_l = (k_col + j - 1 + 64) % 64;
        range_r = (k_col + j + 1) % 64;
        idx_sol = i * 64 + range_r;
        temp += filter[k] * orig[idx_sol];
      }
      sol[idx_orig] = temp;
    }
  }
}