#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk_col:
    for (k_col = 1; k_col < 33; k_col++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        row = j - 1 + k / 32;
        col = k_col - 1 + mod(k, 32);
        val += filter[k] * orig[row * 32 + col];
      }
      sol[j * 32 + k_col - 1] = val;
    }
  }
}