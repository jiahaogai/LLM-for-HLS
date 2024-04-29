#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 64 - 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 128 - 1; i++) {
      idx = i + j * 128;
      oidx = i - 1 + (j - 1) * 128;
      result = orig[oidx] * filter[0] + orig[oidx + 128] * filter[1] + orig[oidx + 2] * filter[2] + orig[oidx + 128 + 2] * filter[3] + orig[oidx + 128 - 1] * filter[4] + orig[oidx + 2 - 1] * filter[5] + orig[oidx + 128 + 2 - 1] * filter[6] + orig[oidx + 128 - 1 - 1] * filter[7] + orig[oidx + 2 - 1 - 1] * filter[8];
      sol[idx] = result;
    }
  }
}