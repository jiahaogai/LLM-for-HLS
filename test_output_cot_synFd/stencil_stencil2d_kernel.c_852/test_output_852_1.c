#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{2}
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
  fs = 1;
  idx = fa - 1;
  idy = fs - 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33 - 1; i++) {
      idx = fa + i;
      idy = fs + j;
      sol[idx + 32 * idy] = ((filter[0] * orig[idx + 32 * idy]) + (filter[1] * (orig[idx + 1 + 32 * idy] + orig[idx - 1 + 32 * idy])) + (filter[2] * (orig[idx + 32 * idy + 1] + orig[idx + 32 * idy - 1])));
    }
  }
}