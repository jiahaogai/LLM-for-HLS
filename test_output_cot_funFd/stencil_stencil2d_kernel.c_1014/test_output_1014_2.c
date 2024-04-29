#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  int flen;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 2;j++) {...} */
  for (j = 1 + 0; j < 33 - 2 + 1; j++) {
    row = j * 32 + 2;
    loopk:
/* Standardize from: for(k = 1;k < 33 - 2;k++) {...} */
    for (k = 1 + 0; k < 33 - 2 + 1; k++) {
      col = k * 32 + 2;
      t = 0;
      loop1:
/* Standardize from: for(i = 0;i < 9;i++) {...} */
      for (i = 0; i < 9 + 0; i++) {
        t += filter[i] * orig[row + ((i - 4) << 5)] + filter[i] * orig[col + ((i - 4) << 5)];
      }
      sol[row + col] = t;
    }
  }
}