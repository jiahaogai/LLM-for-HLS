#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[288];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0 - 1; k++) {
      k_col = ((392 + 0) * (k - 1)) + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0 - 1; i++) {
        i_col = ((392 + 0) * (i - 1)) + 1;
        j_col = ((392 + 0) * (j - 1)) + 1;
        buf[0] = orig[i_col + 0 + ((392 + 0) * 0)];
        buf[1] = orig[i_col + 1 + ((392 + 0) * 0)];
        buf[2] = orig[i_col + 2 + ((392 + 0) * 0)];
        buf[3] = orig[i_col + 3 + ((392 + 0) * 0)];
        buf[4] = orig[i_col + 4 + ((392 + 0) * 0)];
        buf[5] = orig[i_col + 5 + ((392 + 0) * 0)];
        buf[6] = orig[i_col + 6 + ((392 + 0) * 0)];
        buf[7] = orig[i_col + 7 + ((392 + 0) * 0)];
        buf[8] = orig[i_col + 8 + ((392 + 0) * 0)];
        buf[9] = orig[i_col + 9 + ((392 + 0) * 0)];
        buf[10] = orig[i_col + 10 + ((392 + 0) * 0)];
        buf[11] = orig[i_col + 11 + ((392 + 0) * 0)];
        buf[12] = orig[i_col + 12 + ((392 + 0) * 0)];
        buf[13] = orig[i_col + 13 + ((392 + 0) * 0)];
        buf[14] = orig[i_col + 14 + ((392 + 0) * 0)];
        buf[15] = orig[i_col + 15 + ((392 + 0) * 0)];
        buf[16] = orig[i_col + 16 + ((392 + 0) * 0)];
        buf[17] = orig[i_col + 17 + ((392 + 0) * 0)];
        buf[18] = orig[i_col + 18 + ((392 + 0) * 0)];
        buf[19] = orig[i_col + 19 + ((392 +