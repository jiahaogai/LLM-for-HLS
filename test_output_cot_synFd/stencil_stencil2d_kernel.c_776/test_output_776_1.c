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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i * (32 + 2 * 1) + j + pad * k];
      }
      sol[i * (32 + 2 * 1) + j] = t;
    }
  }
}