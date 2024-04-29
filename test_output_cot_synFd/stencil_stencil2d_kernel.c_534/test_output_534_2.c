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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      k_col = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -45; k <= 45; k++) {
        if ((k != 0) && (((8192 + k) % 8190) == i)) {
          if (((8192 + k) / 8190) == j) {
            buff[k_col] = orig[8192 + k];
            k_col++;
          }
        }
      }
      sol[8192 + i + j * 8192] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[8192 + i + j * 8192] += buff[k] * filter[k];
      }
    }
  }
}