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
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1 + 0; k_col < 40 + 0; k_col++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
    for (j_col = 1 + 0; j_col < 40 + 0; j_col++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1 + 0; i_col < 40 + 0; i_col++) {
        sum = 0;
        loopk:
/* Standardize from: for(k = -1;k <= 1;k++) {...} */
        for (k = -1 + 0; k <= 1 + 0; k++) {
          loopj:
/* Standardize from: for(j = -1;j <= 1;j++) {...} */
          for (j = -1 + 0; j <= 1 + 0; j++) {
            loopi:
/* Standardize from: for(i = -1;i <= 1;i++) {...} */
            for (i = -1 + 0; i <= 1 + 0; i++) {
              buf[0] = (i + i_col - 1) + (j + j_col - 1) * 40 + (k + k_col - 1) * 1600;
              sum += orig[buf[0]];
            }
          }
        }
        i = (i_col - 1) + (j_col - 1) * 40 + (k_col - 1) * 1600;
        sol[i] = sum;
      }
    }
  }
}