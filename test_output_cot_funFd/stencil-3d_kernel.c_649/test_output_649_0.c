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
        i_col = (40 * (i - 1)) + 1;
        j_col = (40 * (j - 1)) + 1;
        k_col = (40 * (k - 1)) + 1;
        sum = ((orig[k_col - 1] + orig[k_col + 1]) + (orig[j_col - 1] + orig[j_col + 1])) + (orig[i_col - 1] + orig[i_col + 1]);
        sol[k_col + ((40 * j) + i)] = (sum + (C0 * orig[k_col + ((40 * j) + i)])) / (C1 + 40.0);
      }
    }
  }
}