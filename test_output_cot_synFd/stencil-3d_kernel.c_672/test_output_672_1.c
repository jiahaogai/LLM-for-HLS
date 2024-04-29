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
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        sum = 0;
        loop_buf:
/* Standardize from: for(idx = -12; idx <= 12; idx++) {...} */
        for (idx = ((- 12) + 0); idx <= (12 + 0); idx++) {
          buf[idx + 12] = orig[i_col + idx][j_col + idx][k_col + idx];
          sum += buf[idx + 12];
        }
        sol[i + 40L * (j + 40L * k)] = sum;
      }
    }
  }
}