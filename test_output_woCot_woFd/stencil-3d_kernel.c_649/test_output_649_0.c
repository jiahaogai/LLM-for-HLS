#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = k - 1;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = (j - 1) * 40;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = (i - 1) * 40;
        sum = ((orig[i_col + j_col + k_col] + orig[i_col + 1 + j_col + k_col]) + (orig[i_col + 40 + j_col + k_col] + orig[i_col + 39 + j_col + k_col])) + ((orig[i_col + j_col + k_col + 40] + orig[i_col + 1 + j_col + k_col + 40]) + (orig[i_col + 40 + j_col + k_col + 40] + orig[i_col + 39 + j_col + k_col + 40])) + (orig[i_col + j_col + k_col + 2 * 40] + orig[i_col + 1 + j_col + k_col + 2 * 40]) + (orig[i_col + 40 + j_col + k_col + 2 * 40] + orig[i_col + 39 + j_col + k_col + 2 * 40]) + (orig[i_col + j_col + k_col + 3 * 40] + orig[i_col + 1 + j_col + k_col + 3 * 40]) + (orig[i_col + 40 + j_col + k_col + 3 * 40] + orig[i_col + 39 + j_col + k_col + 3 * 40]);
        sum = sum + ((orig[i_col + j_col + k_col + 5 * 40] + orig[i_col + 1 + j_col + k_col + 5 * 40]) + (orig[i_col + 40 + j_col + k_col + 5 * 40] + orig[i_col + 39 + j_col + k_col + 5 * 40])) + (orig[i_col + j_col + k_col + 6 * 40] + orig[i_col + 1 + j_col + k_col + 6 * 40]) + (orig[i_col + 40 + j_col + k_col + 6 * 40] + orig[i_col + 39 + j_col + k_col + 6 * 40]) + (orig[i_col + j_col + k_col + 7 * 40] + orig[i_col + 1 + j_col + k_col + 7 * 40]) + (orig[i_col + 40 + j_col + k_col + 7 * 40] + orig[i_col + 39 + j_col + k_col + 7 * 40]);
        sum = sum + ((orig[i_col + j_col + k_col + 8 * 40] + orig[i_col + 1 + j_col + k_col + 8 * 40]) + (orig[i_col + 40 + j_col + k_col + 8 * 40] + orig[i_col + 39 + j_col + k_col + 8 * 40])) + (orig[i_col + j_col + k_col + 9 * 40] + orig[i_col + 1 + j_col + k_col + 9 * 40]) + (orig[i_col + 40 + j_col + k_col + 9 * 40] + orig[i_col + 39 + j_col + k_col + 9 * 40]) + (orig[i_col + j_col + k_col + 10 * 40] + orig[i_col + 1 + j_col + k_col + 10 * 40]) + (orig[i_col + 40 + j_col + k_col + 10 * 40] + orig[i_col + 39 + j_col + k_col + 10 * 40]) + (orig[i_col + j_col + k_col + 11 * 40] + orig[i_col + 1 + j_col + k_col + 11 * 40]) + (orig[i_col + 40 + j_col + k_col + 11 * 40] + orig[i_col + 39 + j_col + k_col + 11 * 40]);
        sum = sum + ((orig[i_col + j_col + k_col + 12 * 40] + orig[i_col + 1 + j_col + k_col + 12 * 40]) + (orig[i_col + 40 + j_col + k_col + 12 * 40] + orig[i_col + 39 + j_col + k_col + 12 * 40])) + (orig[i_col + j_col + k_col + 13 * 40] + orig[i_col + 1 + j_col + k_col + 13 * 40]) + (orig[i_col + 40 + j_col + k_col + 13 * 40] + orig[i_col + 39 + j_col + k_col + 13 * 40]) + (orig[i_col + j_col + k_col + 14 * 40] + orig[i_col + 1 + j_col + k_col + 14 * 40]) + (orig[i_col + 40 + j_col + k_col + 14 * 40] + orig[i_col + 39 + j_col + k_col + 14 * 40]) + (orig[i_col + j_col + k_col + 15 * 40] + orig[i_col + 1 + j_col + k_col + 15 * 40]) + (orig[i_col + 40 + j_col + k_col + 15 * 40] + orig[i_col + 39 + j_col + k_col + 15 * 40]);
        sum = sum + ((orig[i_col + j_col + k_col + 16 * 40] + orig[i_col + 1 + j_col + k_col + 16 * 40]) + (orig[i_col + 40 + j_col + k_col + 16 * 40] + orig[i_col + 39 + j_col + k_col + 16 * 40])) + (orig[i_col + j_col + k_col + 17 * 40] + orig[i_col + 1 + j_col + k_col + 17 * 40]) + (orig[i_col + 40 + j_col + k_col + 17 * 40] + orig[i_col +