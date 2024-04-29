#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      t = filter[k_col] * orig[j * 33 + 1 + k_col];
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loopi_col:
      for (i_col = 0; i_col < 32; i_col++) {
        t += filter[k_col] * orig[(j + i_col) * 33 + 1 + k];
      }
      sol[j * 32 + 1 + k] = t;
    }
  }
}