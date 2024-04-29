#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 0;j < 128;j++) {...} */
  for (j = 0; j <= 127; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 0;k < 64;k++) {...} */
    for (k = 0; k <= 63; k++) {
      idx0 = ((j - 1) * 64) + (k - 1);
      idx1 = ((j - 1) * 64) + (k);
      idx2 = ((j - 1) * 64) + (k + 1);
      idx3 = (j * 64) + (k - 1);
      idx4 = (j * 64) + (k);
      idx5 = (j * 64) + (k + 1);
      idx6 = ((j + 1) * 64) + (k - 1);
      idx7 = ((j + 1) * 64) + (k);
      idx8 = ((j + 1) * 64) + (k + 1);
      val = ((orig[idx4] + orig[idx6]) + (orig[idx5] * 2L) + orig[idx7] + orig[idx8]) / 8L;
      sol[idx4] = val;
/* Standardize from: for(k = 0;k < 64;k++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loopk_1:
      for (k = 0; k <= 63; k++) {
        idx = ((j - 1) * 64) + k;
        orig[idx] = sol[idx];
      }
/* Standardize from: for(k = 0;k < 64;k++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loopk_2:
      for (k = 0; k <= 63; k++) {
        idx = (j * 64) + k;
        orig[idx] = sol[idx];
      }
/* Standardize from: for(k = 0;k < 64;k++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loopk_3:
      for (k = 0; k <= 63; k++) {
        idx = ((j + 1) * 64) + k;
        orig[idx] = sol[idx];
      }
    }
  }
}