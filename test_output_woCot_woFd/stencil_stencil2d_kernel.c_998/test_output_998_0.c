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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        i_col = i - 4 + k_col[k];
        j_col = j - 4 + k_col[k];
        t += filter[k] * orig[i_col * 8192 + j_col];
      }
      sol[i * 8192 + j] = t;
    }
  }
}