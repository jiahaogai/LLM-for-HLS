#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      sol[i * 8192 + j] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        i_col = j + ((k % 3) - 1);
        if ((k_col >= 0) && (k_col < 8192) && (i_col >= 0) && (i_col < 8192)) {
          j_col = k_col * 8192 + i_col;
          sol[i * 8192 + j] += orig[j_col] * filter[k];
        }
      }
    }
  }
}