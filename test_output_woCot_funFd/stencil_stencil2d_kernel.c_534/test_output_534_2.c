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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sol[i * 256 + j] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 + k / 3) * 256) + ((k % 3) * 32) + 8;
        i_col = (i * 32) + 8;
        j_col = (j * 32) + 8;
        sol[i * 256 + j] += filter[k] * orig[k_col * 256 + i_col] * orig[j_col * 256 + i_col];
      }
    }
  }
}