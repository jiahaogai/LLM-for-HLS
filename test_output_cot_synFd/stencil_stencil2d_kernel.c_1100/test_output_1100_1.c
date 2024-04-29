#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + ((k % 3) - 1);
        idy = j + ((k / 3) - 1);
        if (idx < 0 || idx >= 256 || idy < 0 || idy >= 256) {
          t += filter[k] * 0;
        }
         else {
          t += filter[k] * orig[idx * 256 + idy];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}