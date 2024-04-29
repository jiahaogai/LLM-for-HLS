#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 128 + 1 - 3; k++) {...} */
  for (k = 16; k <= 128 + -3 + 16; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 128 + 1 - 3; j++) {...} */
    for (j = 16; j <= 128 + -3 + 16; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 128 + 1 - 3; i++) {...} */
      for (i = 16; i <= 128 + -3 + 16; i++) {
        i_col = i - 16;
        j_col = j - 16;
        k_col = k - 16;
        buf[0] = orig[i_col + 1 + (j_col + 1) * 128 + (k_col + 1) * 128 * 128];
        buf[1] = orig[i_col + 1 + j_col * 128 + k_col * 128 * 128];
        buf[2] = orig[i_col + 1 + (j_col + 127) * 128 + (k_col + 1) * 128 * 128];
        buf[3] = orig[i_col + 1 + (j_col + 1) * 128 + (k_col + 127) * 128 * 128];
        buf[4] = orig[i_col + 127 + j_col * 128 + k_col * 128 * 128];
        buf[5] = orig[i_col + 127 + (j_col + 1) * 128 + (k_col + 1) * 128 * 128];
        buf[6] = orig[i_col + 127 + (j_col + 127) * 128 + (k_col + 1) * 128 * 128];
        buf[7] = orig[i_col + 127 + (j_col + 1) * 128 + (k_col + 127) * 128 * 128];
        buf[8] = orig[i_col + (j_col + 1) * 128 + (k_col + 1) * 128 * 128];
        buf[9] = orig[i_col + (j_col + 1) * 128 + (k_col + 127) * 128 * 128];
        buf[10] = orig[i_col + (j_col + 127) * 128 + (k_col + 1) * 128 * 128];
        buf[11] = orig[i_col + (j_col + 127) * 128 + (k_col + 127) * 128 * 128];
        buf[12] = orig[i_col + 1 + (j_col + 127) * 128 + (k_col + 1) * 128 * 128];
        buf[13] = orig[i_col + 1 + (j_col + 127) * 128 + (k_col + 127) * 128 * 128];
        buf[14] = orig[i_col + 127 + (j_col + 127) * 128 + (k_col + 1) * 128 * 128];
        buf[15] = orig[i_col + 127 + (j_col + 127) * 128 + (k_col + 127) * 128 * 128];
        sol[i_col + (j_col + 1) * 16 + (k_col + 1) * 16 * 128] = ((buf[0] + buf[1]) + buf[2]) + ((buf[3] + buf[4]) + buf[5]) + ((buf[6] + buf[7]) + buf[8]) + ((buf[9] + buf[10]) + buf[11]) + ((buf[12] + buf[13]) + buf[14]) + buf[15];
      }
    }
  }
}