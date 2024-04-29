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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf[0] = orig[i_col + (j_col + (k_col + 0 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[1] = orig[i_col + (j_col + (k_col + 1 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[2] = orig[i_col + (j_col + (k_col + 2 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[3] = orig[i_col + (j_col + (k_col + 3 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[4] = orig[i_col + (j_col + (k_col + 4 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[5] = orig[i_col + (j_col + (k_col + 5 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[6] = orig[i_col + (j_col + (k_col + 6 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[7] = orig[i_col + (j_col + (k_col + 7 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[8] = orig[i_col + (j_col + (k_col + 8 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[9] = orig[i_col + (j_col + (k_col + 9 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[10] = orig[i_col + (j_col + (k_col + 10 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[11] = orig[i_col + (j_col + (k_col + 11 * (32 + 1) * (32 + 1)) * (39 + 1)) * (39 + 1)];
        buf[12] = orig[i_col + (j_col + (k_col + 12