Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long index;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L - 3L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L - 3L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L - 3L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        index = i_col + 32L * (j_col + 32L * k_col);
        buf = ((orig[index + 1L]) + (orig[index + 32L]) + (orig[index + 32L * 32L]) + (orig[index + 32L * 32L + 1L]) + (orig[index + 32L * 32L + 32L]) + (orig[index + 32L * 32L + 32L * 2L]) + (orig[index + 32L * 32L + 32L * 3L]) + (orig[index + 32L * 32L + 32L * 4L]) + (orig[index + 32L * 32L + 32L * 5L]) + (orig[index + 32L * 32L + 32L * 6L]) + (orig[index + 32L * 32L + 32L * 7L]) + (orig[index + 32L * 32L + 32L * 8L]) + (orig[index + 32L * 32L + 32L * 9L]) + (orig[index + 32L * 32L + 32L * 10L]) + (orig[index + 32L * 32L + 32L * 11L]) + (orig[index + 32L * 32L + 32L * 12L]) + (orig[index + 32L * 32L + 32L * 13L]) + (orig[index + 32L * 32L + 32L * 14L]) + (orig[index + 32L * 32L + 32L * 15L]) + (orig[index + 32L * 32L + 32L * 16L]) + (orig[index + 32L * 32L + 32L * 17L]) + (orig[index + 32L * 32L + 32L * 18L]) + (orig[index + 32L * 32L + 32L * 19L]) + (orig[index + 32L * 32L + 32L * 2