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
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        if ((((i_col >= 0) && (i_col < 128))) && ((((j + 4) >= 0) && ((j + 4) < 64)))) {
          j_col = j + 4;
          k_col = k_idx[k];
          t += ((orig[i_col * 64 + j_col] * filter[k_col]) >> 4);
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}