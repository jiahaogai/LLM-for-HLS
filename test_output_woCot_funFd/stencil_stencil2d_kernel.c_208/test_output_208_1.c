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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 32 + 2 * 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 0; i < 32 + 2 * 1; i++) {
      idx = i + j * (32 + 2 * 1);
      oidx = pad + i + ((pad + 32) * (pad + j));
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        t += orig[oidx + k * (32 + 2 * 1)] * filter[k];
      }
      sol[idx] = t;
    }
  }
}