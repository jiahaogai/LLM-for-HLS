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
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 9 - 1) - k) % 9;
        i_col = ((8192 + 9 - 1) - k) / 9;
        j_col = j - i_col;
        if ((((i_col >= 0) && (i_col < 8192)) && ((j_col >= 0) && (j_col < 8192))) && ((filter[k]))) {
          t += orig[i_col * 8192 + j_col] * filter[k];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}