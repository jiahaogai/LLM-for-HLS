#ifndef _3D_STENCIL_H_
#define _3D_STENCIL_H_
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{30}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        bound = 392 - 1;
        t1 = ((((orig[i_col + (j_col + (k_col * 392)) * 392] + orig[i_col + ((j_col + 1) + (k_col * 392)) * 392]) + orig[i_col + ((j_col + 1) + ((k_col + 1) * 392)) * 392]) + orig[i_col + (j_col + ((k_col + 1) * 392)) * 392]) + orig[i_col + (k_col * 392)]) + 2;
        t2 = ((((orig[i_col + (((j_col + 1) + (k_col * 392)) * 392)] + orig[i_col + (((j_col + 1) + ((k_col + 1) * 392)) * 392)]) + orig[i_col + (((j_col + 1) + ((k_col + 2) * 392)) * 392)]) + orig[i_col + (((j_col + 1) + ((392 - 2) * 392)) * 392)]) + orig[i_col + (((j_col + 2) + ((k_col + 1) * 392)) * 392)]) + orig[i_col + (((j_col + 2) + ((k_col + 2) * 392)) * 392)]) + 2;
        t3 = ((((orig[i_col + (((j_col + 2) + (k_col * 392)) * 392)] + orig[i_col + (((j_col + 2) + ((k_col + 1) * 392)) * 392)]) + orig[i_col + (((j_col + 2) + ((k_col + 2) * 392)) * 392)]) + orig[i_col + ((((392 - 2) - 1) + ((k_col + 2) * 392)) * 392)]) + orig[i_col