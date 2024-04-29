#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
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
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf[0] = orig[i_col + 40 * (j_col + 40 * k_col)];
        buf[1] = orig[i_col + 40 * (j_col + 40 * (k_col + 1))];
        buf[2] = orig[i_col + 40 * ((j_col + 1) + 40 * k_col)];
        buf[3] = orig[i_col + 40 * ((j_col + 1) + 40 * (k_col + 1))];
        buf[4] = orig[(i_col + 1) + 40 * (j_col + 40 * k_col)];
        buf[5] = orig[(i_col + 1) + 40 * (j_col + 40 * (k_col + 1))];
        buf[6] = orig[(i_col + 1) + 40 * ((j_col + 1) + 40 * k_col)];
        buf[7] = orig[(i_col + 1) + 40 * ((j_col + 1) + 40 * (k_col + 1))];
        sum = 0;
        loop_buf:
        for (long _in_buf = 0; _in_buf < 8; _in_buf++) {
          sum += buf[_in_buf];
        }
        sol[i + 40 * (j + 40 * k)] = sum;
      }
    }
  }
}