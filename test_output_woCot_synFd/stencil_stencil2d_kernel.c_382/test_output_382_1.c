#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 400 - 1; j++) {
      t = 0;
      idx = -1 * filter[0] + i;
      idy = -1 * filter[0];
      inner_idx:
      for (k = 0; k < 9; k++) {
        t += orig[idx][idy] * filter[k];
        idx++;
        idy++;
      }
      sol[i][j] = t;
    }
  }
}