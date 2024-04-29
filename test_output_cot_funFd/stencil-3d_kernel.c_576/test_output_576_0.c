Expected: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[25][25][25];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 25 - 2; k++) {...} */
  for (k = 2; k <= 23; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 2; j < 25 - 2; j++) {...} */
    for (j = 2; j <= 23; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 25 - 2; i++) {...} */
      for (i = 2; i <= 23; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        buf[0][0][0] = orig[i_col + (j_col + (k_col + 0) * 25) * 25];
        buf[0][0][1] = orig[i_col + 1 + (j_col + (k_col + 0) * 25) * 25];
        buf[0][0][2] = orig[i_col + 2 + (j_col + (k_col + 0) * 25) * 25];
        buf[0][1][0] = orig[i_col + (j_col + (k_col + 1) * 25) * 25];
        buf[0][1][1] = orig[i_col + 1 + (j_col + (k_col + 1) * 25) * 25];
        buf[0][1][2] = orig[i_col + 2 + (j_col + (k_col + 1) * 25) * 25];
        buf[0][2][0] = orig[i_col + (j_col + (k_col + 2) * 25) * 25];
        buf[0][2][1] = orig[i_col + 1 + (j_col + (k_col + 2) * 25) * 25];
        buf[0][2][2] = orig[i_col + 2 + (j_col + (k_col + 2) * 25) * 25];
        buf[1][0][0] = orig[i_col + (j_col + (k_col + 0) * 25) * 25];
        buf[1][0][1] = orig[i_col + 1 + (j_col + (k_col + 0) * 25) * 25];
        buf[1][0][2] = orig[i_col + 2 + (j_col + (k_col + 0) * 25) * 25];
        buf[1][1][0] = orig[i_col + (j_col + (k_col + 1) * 25) * 25];
        buf[1][1][1] = orig[i_col + 1 + (j_col + (k_col + 1) * 25) * 25];
        buf[1][1][2] = orig[i_col + 2 + (j_col + (k_col + 1) * 25) * 25];
        buf