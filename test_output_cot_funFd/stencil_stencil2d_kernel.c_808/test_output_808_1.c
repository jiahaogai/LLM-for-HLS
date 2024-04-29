#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{31}
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
  int ftmp[9];
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 128 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1; j++) {
      idx = i - 1;
      idy = j - 1;
      fa = orig[(idx - 1) * 64 + idy - 1];
      fb = orig[idx * 64 + idy - 1];
      fc = orig[(idx + 1) * 64 + idy - 1];
      ftmp[0] = fa;
      ftmp[1] = fb;
      ftmp[2] = fc;
      fa = orig[idx - 1 * 64 + idy];
      fb = orig[idx * 64 + idy];
      fc = orig[idx + 1 * 64 + idy];
      ftmp[3] = fa;
      ftmp[4] = fb;
      ftmp[5] = fc;
      fa = orig[idx - 1 * 64 + idy + 1];
      fb = orig[idx * 64 + idy + 1];
      fc = orig[idx + 1 * 64 + idy + 1];
      ftmp[6] = fa;
      ftmp[7] = fb;
      ftmp[8] = fc;
      sol[i * 64 + j] = ((ftmp[0] + ftmp[1] + ftmp[2]) + (ftmp[3] + ftmp[4] + ftmp[5]) + (ftmp[6] + ftmp[7] + ftmp[8])) / 12.0;
    }
  }
}