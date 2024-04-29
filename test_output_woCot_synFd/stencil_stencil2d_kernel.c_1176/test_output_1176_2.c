*/

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf;
  int idx;
  int idy;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 32; j-- > 32 - 1; ) {
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 32; k-- > 32 - 1; ) {
      idx = k + 32 * j;
      fl = filter[0];
      buf = orig[idx] * fl;
      fl = filter[1];
      buf += orig[idx + 1] * fl;
      fl = filter[2];
      buf += orig[idx + 32] * fl;
      fl = filter[3];
      buf += orig[idx + 33] * fl;
      fl = filter[4];
      buf += orig[idx + 31] * fl;
      sol[idx] = buf;
    }
    loopi:
/* Standardize from: for(i = 1;i < 32 - 1;i++) {...} */
    for (i = 1 + 31; i-- > 31 - 1; ) {
      idx = i + 32 * j;
      fl = filter[0];
      buf = sol[idx] * fl;
      fl = filter[1];
      buf += sol[idx + 1] * fl;
      fl = filter[2];
      buf += sol[idx + 32] * fl;
      fl = filter[3];
      buf += sol[idx + 33] * fl;
      fl = filter[4];
      buf += sol[idx + 31] * fl;
      sol[idx] = buf;
    }
    loopi2:
/* Standardize from: for(i = 1;i < 32 - 1;i++) {...} */
    for (i = 1 + 31; i-- > 31 - 1; ) {
      idx = i + 32 * j;
      fl = filter[5];
      buf = sol[idx] * fl;
      fl = filter[6];
      buf += sol[idx + 1] * fl;
      fl = filter[7];
      buf += sol[idx + 32] * fl;
      fl = filter[8];
      buf += sol[idx + 33] * fl;
      sol[idx] = buf;
    }
  }
  loopj2:
/* Standardize from: for(j = 1;j < 32 - 1;j++) {...} */
  for (j = 1 + 31; j-- > 31 - 1; ) {
    loopk2:
/* Standardize from: for(k = 1;k < 32 - 1;k++) {...} */
    for (k = 1 + 31; k-- > 31 - 1; ) {
      idx = k + 32 * j;
      fl = filter[8];
      buf = sol[idx] * fl;
      sol[idx] = buf;
    }
  }
}