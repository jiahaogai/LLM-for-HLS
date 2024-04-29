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
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2; k <= 39302 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2; j < 39302; j++) {...} */
    for (j = 2; j <= 39302 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 39302; i++) {...} */
      for (i = 2; i <= 39302 - 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        sum = ((C0 * (orig[i_col + 39304 * j_col + 39304 * k_col])) + (C1 * (orig[i_col + 1 + 39304 * j_col + 39304 * k_col] + orig[i_col - 1 + 39304 * j_col + 39304 * k_col] + orig[i_col + 39304 * j_col + 39304 * k_col + 1] + orig[i_col + 39304 * j_col + 39304 * k_col - 1] + orig[i_col + 1 + 39304 * j_col + 39304 * k_col + 1] + orig[i_col - 1 + 39304 * j_col + 39304 * k_col - 1] + orig[i_col + 1 + 39304 * j_col - 1 + 39304 * k_col] + orig[i_col - 1 + 39304 * j_col - 1 + 39304 * k_col])) + (orig[i_col - 1 + 39304 * j_col - 1 + 39304 * k_col]));
        buf[0] = sum;
        sum = ((C0 * (orig[i_col + 39304 * (j_col + 1) + 39304 * k_col])) + (C1 * (orig[i_col + 1 + 39304 * (j_col + 1) + 39304 * k_col] + orig[i_col - 1 + 39304 * (j_col + 1) + 39304 * k_col] + orig[i_col + 39304 * (j_col + 1) + 39304 * k_col + 1] + orig[i_col + 39304 * (j_col + 1) + 39304 * k_col - 1] + orig[i_col + 1 + 39304 * (j_col + 1) + 39304 * k_col + 1] + orig[i_col - 1 + 39304 * (j_col + 1) + 3