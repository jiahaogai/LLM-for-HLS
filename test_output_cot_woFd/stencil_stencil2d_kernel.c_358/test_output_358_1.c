#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        j_col = j - 4;
        k_col = k - 4;
        sol[i] += filter[k] * orig[i_col + k_col] * orig[j_col + k_col];
      }
    }
  }
}