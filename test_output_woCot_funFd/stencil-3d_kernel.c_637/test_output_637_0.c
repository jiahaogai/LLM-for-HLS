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
  
#pragma ACCEL TILE FACTOR=auto{2}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 2;k < 32 + 2;k++) {...} */
  for (k = ((long )2) + bound; k <= 34 + bound; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2;j < 32 + 2;j++) {...} */
    for (j = ((long )2) + bound; j <= 34 + bound; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2;i < 32 + 2;i++) {...} */
      for (i = ((long )2) + bound; i <= 34 + bound; i++) {
        i_col = i - ((long )2);
        j_col = j - ((long )2);
        k_col = k - ((long )2);
        t = ((long )0);
        loopk_col:
/* Standardize from: for(k_col = -2;k_col < 2;k_col++) {...} */
        for (k_col = -((long )2); k_col < 2; k_col++) {
          loopj_col:
/* Standardize from: for(j_col = -2;j_col < 2;j_col++) {...} */
          for (j_col = -((long )2); j_col < 2; j_col++) {
            loopi_col:
/* Standardize from: for(i_col = -2;i_col < 2;i_col++) {...} */
            for (i_col = -((long )2); i_col < 2; i_col++) {
              t += orig[i_col + ((long )32) * (j_col + ((long )32) * k_col)] * mask[i_col + ((long )8) * j_col + ((long )4) * k_col];
            }
          }
        }
        sol[i + ((long )32) * (j + ((long )32) * k)] = t;
      }
    }
  }
}