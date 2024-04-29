#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buff[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        buff[k_col] = orig[((i + ((k_col - 4) * 2)) * 256) + j + ((k_col - 4) * 2)];
      }
      k = 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      while (k < 9) {
        sol[((i * 256) + j) + k] = ((buff[k - 4] + buff[k - 3] + buff[k - 2] + buff[k - 1] + buff[k]) / 5) - filter[k];
        k++;
      }
    }
  }
}