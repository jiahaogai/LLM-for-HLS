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
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1 + ((j - 1) * 40) + ((k - 1) * 40 * 40);
        j_col = j - 1 + ((k - 1) * 40);
        k_col = k - 1;
        sum = C0 * orig[i_col] + C1 * (orig[j_col] + orig[k_col]);
        buf[0] = sum;
        sum = C0 * buf[0] + C1 * (orig[j_col + 40] + orig[k_col + 40 * 40]);
        buf[1] = sum;
        sum = C0 * buf[1] + C1 * (orig[j_col + 2 * 40] + orig[k_col + 2 * 40 * 40]);
        buf[2] = sum;
        sum = C0 * buf[2] + C1 * orig[k_col + 3 * 40 * 40];
        buf[3] = sum;
        sum = C0 * buf[3] + C1 * orig[k_col];
        sol[i_col] = sum;
      }
    }
  }
}