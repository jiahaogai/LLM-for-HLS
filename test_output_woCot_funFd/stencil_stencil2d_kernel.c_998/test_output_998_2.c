#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 8) * k) + i;
        i_col = ((8192 + 8) * i) + k;
        j_col = ((8192 + 8) * j) + k;
        sol[i * 8192 + j] += filter[k] * orig[k_col] * orig[i_col] * orig[j_col];
      }
    }
  }
}