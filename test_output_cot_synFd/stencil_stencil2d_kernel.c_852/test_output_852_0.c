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
  int fl;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i - 1;
      idy = j - 1;
      fl = filter[0];
      sol[idx + idy * 32] = orig[idx + idy * 32] + fl * (orig[idx + idy * 32 - 1] + orig[idx + idy * 32 + 1] + orig[idx + (idy - 1) * 32] + orig[idx + (idy + 1) * 32] + orig[idx - 1 + (idy - 1) * 32] + orig[idx - 1 + (idy + 1) * 32] + orig[idx + 1 + (idy - 1) * 32] + orig[idx + 1 + (idy + 1) * 32]);
    }
  }
}