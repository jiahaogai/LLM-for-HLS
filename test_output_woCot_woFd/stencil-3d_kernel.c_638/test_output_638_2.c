#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 4;k++) {...} */
  for (k = 1 + 4 * 0; k < 4 + 4 * 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1;j < 4;j++) {...} */
    for (j = 1 + 4 * 0; j < 4 + 4 * 0; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 4;i++) {...} */
      for (i = 1 + 4 * 0; i < 4 + 4 * 0; i++) {
        i_col = i - 1 + ((j - 1) * 4) + ((k - 1) * 4 * 4);
        j_col = j - 1 + (k * 4);
        k_col = k - 1;
        t = ((((orig[i_col - 1] + orig[i_col + 1]) + orig[j_col - 1]) + orig[j_col + 1]) + orig[k_col - 1]) + orig[k_col + 1];
        sol[i_col] = ((C0 * (t - orig[i_col])) - (C1 * sol[i_col])) / C1;
      }
    }
  }
}