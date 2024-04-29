#ifndef _1__stencil_3d_
#define _1__stencil_3d_
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        tmp = 2 * orig[index(i, j, k)];
        k_col = index(i, j, (k + 1));
        j_col = index(i, (j + 1), k);
        i_col = index((i + 1), j, k);
        buf[0] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, (k - 1));
        j_col = index(i, (j - 1), k);
        i_col = index((i - 1), j, k);
        buf[1] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, (k + 1));
        j_col = index(i, (j - 1), k);
        i_col = index((i - 1), j, k);
        buf[2] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, (k - 1));
        j_col = index(i, (j + 1), k);
        i_col = index((i - 1), j, k);
        buf[3] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, k);
        j_col = index(i, (j + 1), k);
        i_col = index((i + 1), j, k);
        buf[4] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, (k + 1));
        j_col = index(i, (j - 1), k);
        i_col = index((i + 1), j, k);
        buf[5] = tmp - 1 * orig[k_col] - 1 * orig[j_col] - 1 * orig[i_col];
        k_col = index(i, j, (k - 1));
        j_col = index(i, (j - 1), k);
        i_col = index((i + 1), j, k);
        buf[6] = tmp - 1 * orig