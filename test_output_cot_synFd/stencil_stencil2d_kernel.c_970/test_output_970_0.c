#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fa;
  int fs;
  fa = 0;
  fs = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 32; j++) {
      idx = i - fa;
      idy = j - fs;
      inner:
      for (k = 0; k < 9; k++) {
        if (idx + ((4 - 1) + (k / 3)) >= 0 && idx + ((4 - 1) + (k / 3)) < 32 && idy + ((4 - 1) + (k % 3)) >= 0 && idy + ((4 - 1) + (k % 3)) < 32) {
          sol[i * 32 + j] += orig[idx + ((4 - 1) + (k / 3)) * 32 + idy + ((4 - 1) + (k % 3))] * filter[k];
        }
      }
    }
  }
}