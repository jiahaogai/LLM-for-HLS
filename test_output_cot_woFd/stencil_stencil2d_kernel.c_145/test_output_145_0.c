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
      for (k = 0; k < 9; k++) {
        i_col = i - 1 + d[k];
        j_col = j - 1 + a[k];
        k_col = k;
        t += filter[k] * orig[i_col * (64 + 2) + j_col];
      }
      sol[i * (64 + 2) + j] = t;
    }
  }
}