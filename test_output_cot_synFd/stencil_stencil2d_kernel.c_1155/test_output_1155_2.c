#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i - 1 + (k / 3) * (1 + 2 * 1);
        idy = j - 1 + (k % 3) * (1 + 2 * 1);
        if (idx >= 0 && idx < 32 + 2 * 1 && idy >= 0 && idy < 32 + 2 * 1) {
          t += filter[k] * orig[idx * (32 + 2 * 1) + idy];
        }
      }
      sol[i * (32 + 2 * 1) + j] = t;
    }
  }
}