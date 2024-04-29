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
  int fb;
  int fc;
  int ft;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_sol:
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_filter:
  for (i = 0; i < 9; i++) {
    filter[i] = 0;
  }
  
#pragma ACCEL filter(ft=1)
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopv:
    for (j = 0; j < 8; j++) {
      idx = i - 4 + ((0) >> 2);
      idy = j - 4 + ((0) >> 1);
      fa = (idx >= 0 && idy >= 0 ? orig[idx * 64 + idy] : 0);
      fb = (idx >= 0 && idy < 64 ? orig[idx * 64 + idy + 1] : 0);
      fc = (idx < 64 && idy >= 0 ? orig[idx * 64 + idy + 64] : 0);
      ft = fa + fb + fc;
      sol[i * 64 + j] = ft;
    }
  }
}