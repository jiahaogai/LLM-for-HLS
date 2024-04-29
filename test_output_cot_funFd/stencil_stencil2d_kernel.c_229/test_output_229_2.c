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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      t = filter[k_col] * orig[0 + k_col % 9 * 8];
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 8; i_col++) {
        t += filter[k_col] * orig[i_col + (k_col % 9) * 8];
      }
      sol[j] = t;
    }
    loopj_col:
    for (j_col = 0; j_col < 32; j_col++) {
      orig[j_col] = sol[j_col + 1];
    }
  }
}