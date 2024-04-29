#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      t = 0;
      inner:
      for (k = -1; k < 8; k++) {
        if ((i + k) < 0 || (j + k) < 0 || (i + k) > 63 || (j + k) > 63) {
          t += filter[k + 1] * pad;
        }
         else {
          t += filter[k + 1] * orig[(i + k) * 64 + (j + k)];
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}