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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        sum = ((orig[i_col + 32L * (j_col + 32L * k_col)]) + (orig[i_col + 1L + 32L * (j_col + 32L * k_col)]) + (orig[i_col + 32L * (j_col + 1L + 32L * k_col)]) + (orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)]) + (orig[i_col + 1L + 32L * (j_col + 32L * k_col)]) + (orig[i_col + 32L * (j_col + 1L + 32L * k_col)]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C1 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        buf[0] = sum;
        sum = ((orig[i_col + 32L * (j_col + 32L * (k_col + 1L))]) + (orig[i_col + 1L + 32L * (j_col + 32L * (k_col + 1L))]) + (orig[i_col + 32L * (j_col + 1L + 32L * (k_col + 1L))]) + (orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col + 1L))]) + (orig[i_col + 1L + 32L * (j_col + 32L * (k_col + 1L))]) + (orig[i_col + 32L * (j_col + 1L + 32L * (k_col + 1L))]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 1L))]));
        sum += (C1 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 1L))]));
        buf[1] = sum;
        sum = ((orig[i_col + 32L * (j_col + 32L * (k_col + 2L))]) + (orig[i_col + 1L + 32L * (j_col + 32L * (k_col + 2L))]) + (orig[i_col + 32L * (j_col + 1L + 32L * (k_col + 2L))]) + (orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col + 2L))]) + (orig[i_col + 1L + 32L * (j_col + 32L * (k_col + 2L))]) + (orig[i_col + 32L * (j_col + 1L + 32L * (k_col + 2L))]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 32L * (k_col - 2L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 2L))]));
        sum += (C0 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 2L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col - 2L))]));
        sum += (C0 * (orig[i_col + 1L + 32L * (j_col + 32L * (k_col - 2L))]));
        sum += (C1 * (orig[i_col + 32L * (j_col + 1L + 32L * (k_col - 2L))]));
        buf[2] = sum;
        sum = ((orig[i_col + 32L * (j_col + 32L * (32L + 1L - 1L))]) + (orig[i_col + 1L + 32L * (j_col + 32L * (32L + 1L - 1L))]) + (orig[i_col + 32L * (j_col + 1L + 32L * (32L + 1L - 1L))]) + (orig[i_col + 1L + 32L * (j_