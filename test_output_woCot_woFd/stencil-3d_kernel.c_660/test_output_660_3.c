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
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j-- > 32 + 1; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i-- > 32 + 1; ) {
        i_col = i - 1 + ((j - 1) + ((k - 1) * 32));
        j_col = j - 1 + ((k - 1) * 32);
        k_col = k - 1;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 0) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 0) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 0) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 0) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 0) + ((k_col + 1) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 0) + ((k_col + 1) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 1) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 1) * 32)) * 39304])));
        buf[0] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 1) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 1) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 1) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 1) * 32)) * 39304])));
        buf[1] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 2) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 2) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 2) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 2) * 32)) * 39304])));
        buf[2] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 3) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 3) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 3) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 3) * 32)) * 39304])));
        buf[3] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 4) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 4) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 4) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 4) * 32)) * 39304])));
        buf[4] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 5) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 5) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 5) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 5) * 32)) * 39304])));
        buf[5] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 6) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 6) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 6) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 6) * 32)) * 39304])));
        buf[6] = sum;
        sum = ((C0 * orig[i_col + 0 + ((j_col + 0) + ((k_col + 7) * 32)) * 39304]) + (C1 * (orig[i_col + 1 + ((j_col + 0) + ((k_col + 7) * 32)) * 39304] + orig[i_col + 0 + ((j_col + 1) + ((k_col + 7) * 32)) * 39304] + orig[i_col + 1 + ((j_col + 1) + ((k_col + 7) * 32)) * 39304