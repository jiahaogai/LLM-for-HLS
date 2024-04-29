the `sol` array.

  
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 256; i < 128 + 256 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 256; j < 64 + 256 - 1; j++) {
      i_col = i - 256;
      temp = 0;
      
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i_col + k - 4;
        temp += filter[k] * orig[k_col * 64 + j - 256];
      }
      sol[i * 64 + j] = temp;
    }
  }
}