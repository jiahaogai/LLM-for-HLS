#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long pos;
  long range;
  long err2;
  long err_tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  bound = 32 + 1 - 3;
  range = bound - 1;
  err2 = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
  bound = 32 + 1 - 2;
  range = bound - 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
  bound = 32 + 1 - 1;
  range = bound - 1;
  loopk_col:
  for (k_col = 0; k_col < 32 + 1; k_col++) {
     loopj_col:
     for (j_col = 0; j_col < 32 + 1; j_col++) {
        i_col = 0;
        err_tmp = 0;
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopi_col:
        for (i = 1; i < 32 + 1 - 1; i++) {
          pos = i * 32 * 32 + j * 32 + k * 1;
          err_tmp += ((orig[pos + 1] + orig[pos + 32 + 0] + orig[pos + 32 + 32] + orig[pos + 32]) - (orig[pos] + orig[pos + 32 + 1] + orig[pos + 32 - 1] + orig[pos - 32])) * 8;
          i_col ++;
        }
	err2 += err_tmp;
      }
    }
  }
//#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_sol:
  bound = 32 + 1 - 3;
  range = bound - 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_sol:
  bound = 32 + 1 - 2;
  range = bound - 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopi_sol:
  bound = 32 + 1 - 1;
  range = bound - 1;
  loopk_sol:
  for (k = 1; k < 32 + 1 - 1; k++) {
     loopj_sol:
     for (j = 1; j < 32 + 1 - 1; j++) {
        i = 1;
        sol[i + j * 32 + k * 32 * 32] = 0;
        loopi:
        for (i = 1; i < 32 + 1 - 1; i++) {
          pos = i + j * 32 + k * 32 * 32;
          sol[pos] =