`sol` at the appropriate index.

  
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k1;
  int k2;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128 + 2 * pad; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2 * pad; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      inner:
      for (k2 = 0; k2 < 3; k2++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (k1 = 0; k1 < 3; k1++) {
          t += filter[k1 + k2 * 3] * orig[i - pad + k1 + 128 * (j - pad + 64)];
        }
      }
      sol[i + 128 * j] = t;
    }
  }
}