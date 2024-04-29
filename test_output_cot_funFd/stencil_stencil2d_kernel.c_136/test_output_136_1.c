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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = (i - 4 + 8192) % 8192;
      j_col = (j - 4 + 8192) % 8192;
      k_col = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      while (k_col < 9) {
        k = (k_col + 8192) % 8192;
        sol[i] = ((orig[k] * filter[k_col]) + sol[i]) % 256;
        k_col++;
      }
      i_col++;
      j_col++;
    }
    j_col = (8192 - 4) % 8192;
    i_col = (i + 1) % 8192;
  }
}