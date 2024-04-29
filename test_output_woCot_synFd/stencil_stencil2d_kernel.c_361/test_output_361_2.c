#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (k = -1; k < 2; k++) {
        for (int x = -1; x < 2; x++) {
          t += filter[k + 1] * filter[x + 1] * orig[i * 64 + (j * 8 + k) * 8 + x + pad];
        }
      }
      sol[i * 64 + j * 8 + pad] = t;
    }
  }
}