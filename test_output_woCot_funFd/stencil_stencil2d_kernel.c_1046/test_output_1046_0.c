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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loopj:
  for (j = 0 + 1 + pad; j < 8190 - 1 - pad; j++) {
    
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{64}
    loopi:
    for (i = 0 + 1 + pad; i < 8190 - 1 - pad; i++) {
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i + ((k - 5) * 8190)];
      }
      sol[i + j * 8190] = t;
    }
  }
}