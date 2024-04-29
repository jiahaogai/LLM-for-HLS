#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 64 + 1 - 4;j++) {...} */
  for (j = 1 + 4; j < 64 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      elem = 0;
      
#pragma ACCEL PARALLEL reduction=elem FACTOR=auto{16}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 9 + k_col;
        elem += filter[k] * orig[j * 64 + k_col];
      }
      sol[j * 64 + k_col] = elem;
    }
  }
}