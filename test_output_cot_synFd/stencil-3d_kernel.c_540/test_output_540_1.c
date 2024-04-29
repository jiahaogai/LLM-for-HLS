Code: #pragma ACCEL kernel

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
  for (k = 1 + 32L; k-- > 32L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        sum = ((long )0);
        buf[0] = orig[index(i_col,j_col,k_col)];
        buf[1] = orig[index(i_col,j_col,k - 1L)];
        buf[2] = orig[index(i_col,j_col,k + 1L)];
        buf[3] = orig[index(i_col,j_col - 1L,k)];
        buf[4] = orig[index(i_col,j_col,k)];
        buf[5] = orig[index(i_col,j_col + 1L,k)];
        buf[6] = orig[index(i_col,j_col - 1L,k - 1L)];
        buf[7] = orig[index(i_col,j_col,k - 1L)];
        buf[8] = orig[index(i_col,j_col + 1L,k - 1L)];
        buf[9] = orig[index(i_col,j_col - 1L,k + 1L)];
        buf[10] = orig[index(i_col,j_col,k + 1L)];
        buf[11] = orig[index(i_col,j_col + 1L,k + 1L)];
        buf[12] = orig[index(i_col - 1L,j_col,k)];
        buf[13] = orig[index(i_col,j_col,k)];
        buf[14] = orig[index(i_col + 1L,j_col,k)];
        buf[15] = orig[index(i_col - 1L,j_col,k - 1L)];
        buf[16] = orig[index(i_col,j_col,k - 1L)];
        buf[17] = orig[index(i_col + 1L,j_col,k - 1L)];
        buf[18] = orig[index(i_col - 1L,j_col,k + 1L)];
        buf[19] = orig[index(i_col,j_col,k + 1L)];
        buf[20] = orig[index(i_col + 1L,j_col,k + 1L)];
        buf[21] = orig[index(i_col - 1L,j_col - 1L,k)];
        buf[22] = orig[index(i_col,j_