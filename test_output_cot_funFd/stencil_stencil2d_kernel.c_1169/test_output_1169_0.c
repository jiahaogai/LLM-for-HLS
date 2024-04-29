#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      idx = i * (32 + 2 * 1) + j;
      oidx = (i - 1) * (32 + 2 * 1) + j - 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{9}
      inner:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[oidx + k_par * (32 + 2 * 1)];
      }
      sol[idx] = t;
    }
  }
}